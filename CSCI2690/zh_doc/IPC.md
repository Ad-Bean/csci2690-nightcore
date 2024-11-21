## 进程间通信 ipc

`src/ipc/base.cpp` 定义了 namespace `faas::ipc`

具有三种通信方法：

- unix
- shared memory
- fifo/pipe

`SetRootPathForIpc` 方法接受 `--root_path_for_ipc=/tmp/nightcore/ipc` 参数和 `create=true`

会创建相应的三种通信方法的

spsc, 单消费单生产无锁队列

## base

thread 库，使用 pthread + thread local + state 管理线程，`MarkThreadCategory` 标记 cpu affinity 绑定线程到 cpu

logging 库

## common

uv 库，封装 libuv 事件循环

time 库，时间转换

subprocess 子进程，利用 pipe 通信（写 bufferpool），uv 管理状态

http status 库

func config 库，用 map 维护 func_name to Entry, Entry 维护 grpc 状态或 http 状态

protocol.h 定义函数调用和消息传递，Message, GatewayMessage

## server

server_base 是一个 uv 线程，

## gateway

server 打开 http/grpc port 监听客户端请求，维护 func config 转发请求

## bin

## engine
