## 进程间通信

`src/ipc/base.cpp` 定义了 namespace `faas::ipc`

具有三种通信方法：

- unix
- shared memory
- fifo/pipe

`SetRootPathForIpc` 方法接受 `--root_path_for_ipc=/tmp/nightcore/ipc` 参数和 `create=true`

会创建相应的三种通信方法的

spsc, 单消费单生产无锁队列
