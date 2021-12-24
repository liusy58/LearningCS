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
    | Client-to-server binding using a daemon|The daemon keeps track of the current end point of each service implemented by a co-located server. The daemon itself listens to a well-known end point. A client will first contact the daemon, request the end point, and then contact the specific server.|<img src="../img/03-13a.png" alt="l" style="width:300px;"/>|
    | Client-to-server binding using a superserver|have a single superserver listening to each end point associated with a specific service.When a request comes in, the daemon forks a process to handle it. (eg,inetd)|<img src="../img/03-13b.png" alt="l" style="width:300px;"/>|


###  Interrupting a server
???+note "How to interrupt a server?"
    |Ways|characteristics|
    |-|-|
    |Users  abruptly exit the client application||
    |Send out-of-band data||

### Stateless versus stateful servers

???+note "State of servers"
    |Type|Characteristics|examples|
    |-|-|-|
    |stateless server|not keep information on the state of its clients, and can change its own state without having to inform any client|A Web Server|
    |soft state| The server promises to maintain state on behalf of the client, but only for a limited time|A server promising to keep a client informed about updates, but only for a limited time. |
    |stateful server|maintains persistent information on its clients| A file server that allows a client to keep a local copy of a file, even for performing update operations. |


???+info "cookies"
    Information that often transparently stored by the client’s browser will be sent to the server. 


### Object   servers
  
 


### Example: The Apache Web server

