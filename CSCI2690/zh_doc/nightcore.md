##

nightcore 需要重新 redeploy gateway 来添加新函数

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
