### Concurrent versus iterative servers

???+note "Two ways to organize servers"
    |type|characteristic|
    |-|-|
    |iterative server|the server itself handles the request and, if necessary, returns a response to the requesting client|
    |concurrent server| It does not handle the request itself, but passes it to a separate thread or another process, after which it immediately waits for the next incoming request. |

### Contacting a server: end points

???+note "Service without a preassigned end point"
    |type|characteristics||
    |-|-|-|
    | Client-to-server binding using a daemon|The daemon keeps track of the current end point of each service implemented by a co-located server. The daemon itself listens to a well-known end point. A client will first contact the daemon, request the end point, and then contact the specific server.|<img src="../img/03-13a.png" alt="l" style="width:200px;"/>|
    | Client-to-server binding using a superserver|have a single superserver listening to each end point associated with a specific service.When a request comes in, the daemon forks a process to handle it. |<img src="../img/03-13b.png" alt="l" style="width:200px;"/>|


###  Interrupting a server
???+note "How to interrupt a server?"
    |||
    |-|-|
    |Users  abruptly exit the client application||
    |Send out-of-band data||

### Stateless versus stateful servers

    
 
