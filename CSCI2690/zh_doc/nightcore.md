## drawbacks

nightcore 需要重新 redeploy gateway 来添加新函数

参见 `nightcore/examples/go/run_stack.sh` 可以发现，gateway 和 engine 都需要重新运行

首先是因为需要提前手动设置 func id，没有自增机制

而且实际上函数是状态机进程，使用 FIFO 通信？

这样 hotelreservations 如果需要函数之间通信，就可以通过配置直接通信，gateway 不再是 single point of failure

因为

```docker
  nightcore-gateway:
    image: zjia/nightcore:asplos-ae
    ports:
      - 8080:8080
    entrypoint:
      - /nightcore/gateway
      - --listen_addr=0.0.0.0
      - --http_port=8080
      - --func_config_file=/tmp/nightcore/func_config.json
      - --num_io_workers=4
      - --lb_pick_least_load
      - --max_running_requests=48
    volumes:
      - /tmp/nightcore_config.json:/tmp/nightcore/func_config.json
```

nightcore 使用 libuv(epoll) 和事件循环来处理函数

## IPC

以 hotel reservation 举个例子

search 是怎么进行 inter-function communication 的

search 需要重写，使用 nightcore runtime / worker

`./workloads/DeathStarBench/hotelReservation/cmd/frontend/main.go` 入口是 `faas.Serve()`

### Nightcore worker

`workloads/DeathStarBench/hotelReservation/worker/lib.go`

`SetRootPathForIpc` 需要设定 ipc 用于函数间通信

`FAAS_MSG_PIPE_FD` 用于和 engine 通信

并且会启动一些 `FuncWorker`

`FuncWorker.Run()`

1. `doHandshake`
   1. 打开 unix socket 和 engine 通信
   2. 打开自己的 fifo 通信
   3. 写入 engine 表示当前调用，读取 engine 进行握手
   4. 通过 `entriesByFuncId` 寻找对应的配置和 FuncId
   5. 如果是 gRPC 就创建 grpcHandler 工厂，否则只是普通 Handler
   6. 打开 FIFO 等待写入
2. `go w.servingLoop()`
3. 当前线程死循环读 fifo pipe
   1. 如果是 `MessageType_DISPATCH_FUNC_CALL`
      1. 传入 `newFuncCallChan`
      2. `servingLoop` 协程
   2. 如果是 `MessageType_FUNC_CALL_COMPLETE` 或失败
      1. 找到对应的 funcCall
      2. mutex lock `outgoingFuncCalls map[uint64](chan []byte)`
      3. 如果对应的 funcCall 存在，消费塞入队列 `outgoingFuncCalls[funcCall.FullCallId()]` 后删除
      4. mutex unlock

`workloads/DeathStarBench/hotelReservation/worker/worker/func_worker.go`

1. 执行 `executeFunc` 一旦 `newFuncCallChan` channel 有消息
2.
