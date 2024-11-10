## QPS 100

command:

```bash
wrk -t 4 -c 64 -d 30 -L -U -s ./mixed-workload_type_1.lua "http://hp078.utah.cloudlab.us:8080" -R 100
```

result:

```
Running 30s test @ http://hp078.utah.cloudlab.us:8080
  4 threads and 64 connections
  Thread calibration: mean lat.: 91.381ms, rate sampling interval: 180ms
  Thread calibration: mean lat.: 90.947ms, rate sampling interval: 180ms
  Thread calibration: mean lat.: 91.987ms, rate sampling interval: 181ms
  Thread calibration: mean lat.: 90.559ms, rate sampling interval: 180ms
  Thread Stats   Avg      Stdev     Max   +/- Stdev
    Latency    88.73ms   19.12ms 402.18ms   97.63%
    Req/Sec    24.79     33.48    89.00     75.68%
  Latency Distribution (HdrHistogram - Recorded Latency)
 50.000%   86.27ms
 75.000%   88.19ms
 90.000%   90.88ms
 99.000%  149.12ms
 99.900%  397.82ms
 99.990%  402.43ms
 99.999%  402.43ms
100.000%  402.43ms

  Detailed Percentile spectrum:
       Value   Percentile   TotalCount 1/(1-Percentile)

      80.191     0.000000            1         1.00
      83.647     0.100000          206         1.11
      84.415     0.200000          409         1.25
      85.055     0.300000          606         1.43
      85.695     0.400000          804         1.67
      86.271     0.500000         1002         2.00
      86.591     0.550000         1101         2.22
      86.911     0.600000         1198         2.50
      87.295     0.650000         1301         2.86
      87.679     0.700000         1395         3.33
      88.191     0.750000         1493         4.00
      88.511     0.775000         1543         4.44
      88.895     0.800000         1593         5.00
      89.279     0.825000         1649         5.71
      89.599     0.850000         1689         6.67
      90.175     0.875000         1737         8.00
      90.495     0.887500         1764         8.89
      90.879     0.900000         1788        10.00
      91.199     0.912500         1811        11.43
      91.711     0.925000         1836        13.33
      92.543     0.937500         1861        16.00
      93.375     0.943750         1876        17.78
      93.567     0.950000         1895        20.00
      93.695     0.956250         1899        22.86
      94.335     0.962500         1910        26.67
      95.359     0.968750         1922        32.00
      96.639     0.971875         1929        35.56
     100.159     0.975000         1935        40.00
     128.447     0.978125         1941        45.71
     137.087     0.981250         1947        53.33
     143.999     0.984375         1953        64.00
     147.327     0.985938         1959        71.11
     147.455     0.987500         1960        80.00
     149.119     0.989062         1964        91.43
     149.247     0.990625         1966       106.67
     150.911     0.992188         1969       128.00
     152.575     0.992969         1971       142.22
     153.471     0.993750         1972       160.00
     156.415     0.994531         1974       182.86
     157.695     0.995313         1975       213.33
     159.231     0.996094         1977       256.00
     161.535     0.996484         1978       284.44
     161.535     0.996875         1978       320.00
     389.887     0.997266         1979       365.71
     395.519     0.997656         1980       426.67
     397.567     0.998047         1981       512.00
     397.567     0.998242         1981       568.89
     397.567     0.998437         1981       640.00
     397.823     0.998633         1982       731.43
     397.823     0.998828         1982       853.33
     399.615     0.999023         1983      1024.00
     399.615     0.999121         1983      1137.78
     399.615     0.999219         1983      1280.00
     399.615     0.999316         1983      1462.86
     399.615     0.999414         1983      1706.67
     402.431     0.999512         1984      2048.00
     402.431     1.000000         1984          inf
#[Mean    =       88.730, StdDeviation   =       19.124]
#[Max     =      402.176, Total count    =         1984]
#[Buckets =           27, SubBuckets     =         2048]
----------------------------------------------------------

  Latency Distribution (HdrHistogram - Uncorrected Latency (measured without taking delayed starts into account))
 50.000%   85.44ms
 75.000%   87.29ms
 90.000%   90.05ms
 99.000%  148.74ms
 99.900%  397.82ms
 99.990%  400.64ms
 99.999%  400.64ms
100.000%  400.64ms

  Detailed Percentile spectrum:
       Value   Percentile   TotalCount 1/(1-Percentile)

      79.615     0.000000            1         1.00
      82.943     0.100000          214         1.11
      83.583     0.200000          407         1.25
      84.223     0.300000          611         1.43
      84.863     0.400000          810         1.67
      85.439     0.500000          993         2.00
      85.823     0.550000         1108         2.22
      86.079     0.600000         1197         2.50
      86.399     0.650000         1292         2.86
      86.783     0.700000         1390         3.33
      87.295     0.750000         1498         4.00
      87.615     0.775000         1545         4.44
      87.935     0.800000         1589         5.00
      88.383     0.825000         1644         5.71
      88.831     0.850000         1691         6.67
      89.343     0.875000         1738         8.00
      89.663     0.887500         1761         8.89
      90.047     0.900000         1789        10.00
      90.367     0.912500         1813        11.43
      90.815     0.925000         1836        13.33
      91.711     0.937500         1861        16.00
      92.223     0.943750         1875        17.78
      92.479     0.950000         1885        20.00
      92.863     0.956250         1898        22.86
      93.503     0.962500         1911        26.67
      94.463     0.968750         1922        32.00
      96.063     0.971875         1929        35.56
      98.687     0.975000         1935        40.00
     127.295     0.978125         1941        45.71
     136.831     0.981250         1947        53.33
     142.975     0.984375         1953        64.00
     146.943     0.985938         1959        71.11
     147.071     0.987500         1960        80.00
     148.479     0.989062         1963        91.43
     148.991     0.990625         1966       106.67
     149.503     0.992188         1969       128.00
     152.063     0.992969         1971       142.22
     152.319     0.993750         1973       160.00
     155.391     0.994531         1974       182.86
     156.159     0.995313         1975       213.33
     158.463     0.996094         1977       256.00
     160.639     0.996484         1978       284.44
     160.639     0.996875         1978       320.00
     389.119     0.997266         1979       365.71
     394.239     0.997656         1980       426.67
     396.543     0.998047         1981       512.00
     396.543     0.998242         1981       568.89
     396.543     0.998437         1981       640.00
     397.823     0.998633         1982       731.43
     397.823     0.998828         1982       853.33
     399.103     0.999023         1983      1024.00
     399.103     0.999121         1983      1137.78
     399.103     0.999219         1983      1280.00
     399.103     0.999316         1983      1462.86
     399.103     0.999414         1983      1706.67
     400.639     0.999512         1984      2048.00
     400.639     1.000000         1984          inf
#[Mean    =       87.915, StdDeviation   =       19.121]
#[Max     =      400.384, Total count    =         1984]
#[Buckets =           27, SubBuckets     =         2048]
----------------------------------------------------------
  3008 requests in 30.09s, 1.21MB read
Requests/sec:     99.97
Transfer/sec:     41.16KB
```