???+note "RPC"
    When a process on machine A calls a procedure on machine B, the calling process on A is suspended, and execution of the called procedure takes place on B. Information can be transported from the caller to the callee in the parameters and can come back in the procedure result. No message passing at all is visible to the programmer. This method is known as remote procedure call, or often just RPC.

### Basic RPC operation

???+info "Strps of RPC"
    1. The client procedure calls the client stub in the normal way.

    2. The client stub builds a message and calls the local operating system.
    
    3.The client’s OS sends the message to the remote OS.
    
    4.The remote OS gives the message to the server stub.
    
    5.The server stub unpacks the parameter(s) and calls the server.
    
    6.The server does the work and returns the result to the stub.
    
    7.The server stub packs the result in a message and calls its local OS.
    
    8.The server’s OS sends the message to the client’s OS.
    
    9.The client’s OS gives the message to the client stub.
    
    10.The stub unpacks the result and returns it to the client.

    <img src="../img/04-07.png" alt="l" style="width:400px;"/>

    
    