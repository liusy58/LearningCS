# 使用 Prometheus 指标库

Prometheus 是常用的指标库之一，它只需要开发者提供一个 HTTP 接口，在这个接口使用纯文本返回一系列指标值即可，例如：

```
requests_served 12345
uptime 25.23
operations{ops="GET"} 234
```

可以看到，这就是一个简单的带标签的 Key 到 Float 的映射。我们可以自己整合 HTTP 服务器来提供这个接口，也可以使用现成的库来提供。

Prometheus 并不是一个基于事件的监控系统，也就是说不能来一个请求就上报一次指标，而是要在进程内部先计算好指标，例如增加一个计数器。

## 拉（Pull）模式

Prometheus 常用的是拉模式的上报模式。在拉模式下，服务进程并不会主动向指标系统汇报指标，而是由指标系统根据**采样间隔**，定时地去访问服务进程提供的指标接口，然后保存到**时序数据库**中。

???+note "采样间隔的设置"
    一般来说，采样间隔会设置在 10s 左右，采样间隔过长会导致数据更新频率低，不能很好地反映系统状况，而采样间隔过短一方面会导致服务进程需要消耗更多的资源生成指标数据，另一方面需要存储的数据点也更多，在指标聚合的时候计算量也更大。

## 推（Push）模式

在极少数的情况下，可以使用 Push Gateway 来主动上报指标数据。比如，你有一个批处理任务，运行完之后进程就结束了，这时候指标系统就没有办法拉取到指标数据，需要进程在结束之前上报一次数据到长时间运行的服务进程暂时保存下来，Prometheus 再去使用拉模式从这个服务进程，也就是 Push Gateway 去拉取数据。

???+note "推拉模式的比较"
    你会觉得，拉模式需要指标系统知道有哪些服务要拉取，这个需要额外的配置，而且需要一个中心进程来负责拉取数据，可能不能很好的扩展。但是推模式下，监控系统没有办法知道一个进程到底只是长时间没有指标上报，还是进程挂掉了，实际上监控系统还是要知道需要监控哪些进程。而且在拉模式下，监控系统有着统一的控制，可以避免过载的现象。而在推模式下，如果上报频率过高，会占用大量网络流量，可能影响正常服务，并且如果监控系统没有做好过载限流保护，可能导致监控进程崩溃等严重后果。在采样间隔比较长的情况下，拉模式其实并不会对监控系统造成过大的影响。