## Docker Compose

run the following in one of the `./experiments`, like `./experiments/hotelresv_singlenode`

```bash
sudo rm -rf /tmp/nightcore_config.json
sudo rm -rf /tmp/run_launcher
sudo rm -rf /mnt/inmem/nightcore
sudo mkdir -p /mnt/inmem/nightcore
sudo mkdir -p /mnt/inmem/nightcore/output /mnt/inmem/nightcore/ipc

cp ./nightcore_config.json /tmp/nightcore_config.json
cp ./run_launcher /tmp/run_launcher
sudo cp /tmp/run_launcher /mnt/inmem/nightcore/run_launcher
sudo cp /tmp/nightcore_config.json /mnt/inmem/nightcore/func_config.json


docker-compose up
```

engine cpu:

```bash
ENGINE_CONTAINER_ID=$(docker inspect --format='{{.Id}}' $(docker ps -q -f name="nightcore-engine"))
echo 4096 | sudo tee /sys/fs/cgroup/cpu/docker/$ENGINE_CONTAINER_ID/cpu.shares
```

## wrk1 benchmark

```bash
wrk -t5 -c55 -d5 --latency "http://localhost:8080/function/user?username=Cornell_1&password=1111111111"
```

## Git

```bash
git submodule update --remote
git submodule update --init --recursive
```
