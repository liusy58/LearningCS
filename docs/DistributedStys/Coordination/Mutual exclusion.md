???+note "categories of distributed mutual exclusion algorithms"
    |type|advantage|disadvantage|
    |-|-|-|
    |token-based solutions|1. avoid starvation 2. avoid deadlock| When the token is lost,  an intricate distributed procedure needs to be started|
    |permission-based approach|||


???+note 
    |Algorithm|Definition|Advantage|Disadvantage|Graphics|
    |-|-|-|-|-|
    |A centralized algorithm|A process is elected as the coordinator. Whenever a process wants to access a shared resource, it send request to the coordinator for permission. |1. It's fair. 2. No starvation. 3. Easy to implement. |1. If the coordinator crashes, the entire system may go down.2.a single coordinator can become a performance bottleneck.|<img src="../img/06-15a.png" alt="l" style="width:400px;"/><img src="../img/06-15b.png" alt="l" style="width:400px;"/><img src="../img/06-15c.png" alt="l" style="width:400px;"/>|
    |A distributed algorithm|When a process wants to access a shared resource, it sends the message to all other and then sits back and waits until everyone else has given permission.|1. No starvation. 2. No deadlock.|1. Any process crashes will cause the entire system to fail. 2. Multicast communication will lead to much resource consumption.|<img src="../img/06-16a.png" alt="l" style="width:400px;"/><img src="../img/06-16b.png" alt="l" style="width:400px;"/><img src="../img/06-16c.png" alt="l" style="width:400px;"/>|
    |A token-ring algorithm|Token circulates aroud the ring and when a process acquires the token, it checks to see if it needs to access the shared resouce.|1. No starvation.|1. If the token is ever lost, it must be regenerated. |<img src="../img/06-16c.png" alt="l" style="width:400px;"/>|
    |A decentralized algorithm|Each resource is assumed to be replicated N times. Every replica has its own coordinator for controlling the access by concurrent processes.  whenever a process wants to access the resource, it will simply need to get a majority vote from m > N/2 coordinators. ||1. When a coordinator crashes, it recovers quickly but will have forgotten any vote it gave before it crashed. 2.  If many nodes want to access the same resource, it turns out that the utilization rapidly drops.||