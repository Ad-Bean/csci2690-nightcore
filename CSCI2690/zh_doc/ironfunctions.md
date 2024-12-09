## Ironfunctions

`docker run --rm -it --name functions -v ${PWD}/data:/app/data -v /var/run/docker.sock:/var/run/docker.sock -p 8080:8080 iron/functions`

启动容器 `-v` 挂载当前目录 `data`

`-v /var/run/docker.sock:/var/run/docker.sock`：将主机的 Docker 套接字文件挂载到容器内，以便容器可以访问 Docker 引擎

## server

### NewFromEnv

`funcServer := server.NewFromEnv(ctx)`

根据 `EnvDBURL` `EnvMQURL` 启动，连接挂载的 boltdb 文件

也就是 `bolt://%s/data/worker_mq.db` 和 `bolt://%s/data/bolt.db?bucket=funcs` 文件

会启动 MQ 和 BoltDB

以及一个 gin 路由，使用 log, jwt 中间件

`/` ping
`/version` version
`/stats`

`GET /v1/apps` 获取当前 functions 调用 `handleAppList`
`POST /v1/apps` 创建任务 调用 `handleAppCreate`

GET/PATCH/DELETE `/v1/apps/:app`

GET `/v1/routes`

GET/DELETE `/tasks`

GET `/r/:app/*route` 调用 `server.handleRunnerRequest(c, s.Enqueue)`

`type Enqueue func(context.Context, MessageQueue, *Task) (*Task, error)`
是一个函数类型

### Start

`startGears` 监听接口

`supervisor.Supervisor` 管理多个并发任务

1. 监听 `http.Serve(listener, s.Router)`，也就是 gin 的路由

> TODO: 加入 grpc

## handleRequest

`api/server/runner.go`

负责 dispatch 任务

1. 处理 GET / POST 请求，处理 reqRoute 从 Datastore 获取 app
2. `FireBeforeDispatch` ？
3. `loadroutes` 获取路由，其中 `routecache.Cache` 带有缓存
   `singleflight` 用于确保在并发环境中，对于相同的请求（由相同的键标识），只会有一个执行函数在运行，其他

4. `s.serve` 调用 `runner/worker` 塞任务到 server.tasks channel
   Runner driver 驱动 docker 容器
   `Runner.Enqueue()`
   `runner.RunTask(s.tasks, ctx, cfg)`

## FN tools

`fn init` 创建 yaml

`fn build` 创建 image

`fn create :app` POST apps 接口创建 app，放入 datastore InsertApp

`fn routes create :app /path` 创建路由

### FN BUILD

```go
type Funcfile struct {
	Name           string            `yaml:"name,omitempty" json:"name,omitempty"`
	Version        string            `yaml:"version,omitempty" json:"version,omitempty"`
	Runtime        *string           `yaml:"runtime,omitempty" json:"runtime,omitempty"`
	Entrypoint     string            `yaml:"entrypoint,omitempty" json:"entrypoint,omitempty"`
	Cmd            string            `yaml:"cmd,omitempty" json:"cmd,omitempty"`
	Type           *string           `yaml:"type,omitempty" json:"type,omitempty"`
	Memory         *int64            `yaml:"memory,omitempty" json:"memory,omitempty"`
	Format         *string           `yaml:"format,omitempty" json:"format,omitempty"`
	Timeout        *time.Duration    `yaml:"timeout,omitempty" json:"timeout,omitempty"`
	IDLETimeout    *time.Duration    `yaml:"idle_timeout,omitempty" json:"idle_timeout,omitempty"`
	Headers        map[string]string `yaml:"headers,omitempty" json:"headers,omitempty"`
	Config         map[string]string `yaml:"config,omitempty" json:"config,omitempty"`
	Build          []string          `yaml:"build,omitempty" json:"build,omitempty"`
	Tests          []fftest          `yaml:"tests,omitempty" json:"tests,omitempty"`
	Path           *string           `yaml:"path,omitempty" json:"path,omitempty"`
	MaxConcurrency *int              `yaml:"max_concurrency,omitempty" json:"max_concurrency,omitempty"`
	JwtKey         *string           `yaml:"jwt_key,omitempty" json:"jwt_key,omitempty"`
}
```

## Runner

```go
type Runner struct {
	driver       drivers.Driver
	taskQueue    chan *containerTask
	mlog         MetricLogger
	flog         FuncLogger
	availableMem int64
	usedMem      int64
	usedMemMutex sync.RWMutex

	stats
}
```

会启动一个 docker driver

`func (r *Runner) Run` 会启动 docker 容器 `r.driver.Prepare(ctx, ctask)`

## Optimization

1. docker 进程加上 IPC 和 mount shared memory 用于 grpc 通信

## customized image/func.yaml

1. `root_path_for_ipc` `/dev/shm/faas_ipc`
2. `func_id`
