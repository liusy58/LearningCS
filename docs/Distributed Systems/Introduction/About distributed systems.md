???+note "Why make a system distributed?"
    |Reason|Example|
    |-|-|
    |Some applications are inherently distributed|Sending a message from your phone to your friend's phone.|
    |For better reliability|The system as a whole keeps functioning even if one node fails.|
    |For better performance|Get data from a nearby node rather than one halfway around the world.|
    |To solve bigger problems|Huge amounts of data which can't fit on one machine.|


???+note "Why not make a system distributed?"
    |Reason|Example|
    |-|-|
    |Communication may fail||
    |Process may crash||
    |Fault tolerance||



### Distributed systems and computer networking

???+note 
    The study of distributed systems builds upon computer networks, and instead focuses on how several nodes should coordinate by computer networks to achieve some shared task. So the detail about networking is not important. 


### Example: Remote Procedure Calls (RPC)
???+note "RPC"
    The type of interaction, where code on one node appears to call a function on another node, is called a Remote Procedure Call.

???+note "How RPC works?"
    When an application wishes to  call a function on another node, the RPC framework provides a stub in its place. The stub has the same type signature as the real function, but instead of executing the real function, it encodes the function arguments in a message and sends that message to the remote node, asking for that function to be called.
    <img src="../img/rpc.png" alt="l" style="width:500px;"/>    


???+note "REST"
    Today, the most common form of RPC is implemented using JSON data sent over HTTP. A popular set of design principles for such HTTP-based APIs is known as representational state transfer or REST, and APIs that adhere to these principles are called RESTful. These principles include:

    1. communication is stateless (each request is self-contained and independent from other requests),

    2. resources (objects that can be inspected and manipulated) are represented by URLs, and

    3. the state of a resource is updated by making a HTTP request with a standard method type, such as POST or PUT, to the appropriate URL.

    The popularity of REST is due to the fact that JavaScript code running in a web browser can easily make this type of HTTP request.

    
