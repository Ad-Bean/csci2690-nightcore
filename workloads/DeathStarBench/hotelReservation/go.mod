module github.com/harlow/go-micro-services

go 1.14

require (
	cs.utexas.edu/zjia/faas v0.0.0
	github.com/bradfitz/gomemcache v0.0.0-20190913173617-a41fca850d0b
	github.com/golang/protobuf v1.4.0
	github.com/hailocab/go-geoindex v0.0.0-20160127134810-64631bfe9711
	github.com/stretchr/testify v1.9.0 // indirect
	google.golang.org/grpc v1.28.0
	google.golang.org/protobuf v1.23.0
	gopkg.in/check.v1 v1.0.0-20201130134442-10cb98267c6c // indirect
	gopkg.in/mgo.v2 v2.0.0-20190816093944-a6b53ec6cb22
	gopkg.in/yaml.v2 v2.4.0 // indirect
)

replace cs.utexas.edu/zjia/faas => /src/nightcore/worker/golang

// replace cs.utexas.edu/zjia/faas => ./worker/golang
