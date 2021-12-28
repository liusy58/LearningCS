???+note "Goals of distributed systems"
    |Goal|Definition|
    |-|-|
    |Making resource available||
    |Distribution transparency|Access, Loaction, Migration, Relocation, Replication, concurrency, failure|
    |Openness|System should conform to well-defined interfaces, support portability of applications and easily interoperate.|
    |Scalability||

???+note "policy vs. mechanism"
    Take scheduling processes for example, policy is that "OS can schedule", mechanism is that "how to schedule these processes"

???+note "Types of Distributed Systems"
    |||
    |-|-|
    |Distributed computing systems||
    |Distributed information systems||
    |Distributed pervasive systems|| 

???+note "Distributed Computing Systems"
    |||
    |-|-| 
    |Cluster Computing|Homogeneous:same OS; |
    |Grid Computing|heterogeneous; Dispersed across several organizations; Span a wide-area network|





???+note "Why replication?"
    |||
    |-|-|
    |Reliability|Avoid single points of failure|
    |Performance|Scalability in numbers and geographic areas|

???+note "Data-centric model and Client-centric model"
    Data-centric consistency models aim at providing a systemwide consistent view on a data store. It deals with concurrent wrting. Client-centric model aims at dealing with these cases where users may sometimes operate on different replicas while updates have not been fully propagated.

???+note "Consistency model"
    |||
    |-|-|
    |Strict Consistency|Rely on absolute global time|
    |Linearizability|timestap order|
    |Sequential|no requirement for timestap order|
    |Casual|Writes that are potentially causally related must be seen by all processes in the same order|
    |FIFO|Writes done by a single process are seen by all other process in the order in which they are issued, but writes from different processes may be seen in adifferent order by different process|
    |Weak|Access to synchronization variables associated with a data store are sequentially consistent|
    |Release||
    |Entry||
    |Monotonic Reads|If a process reads the value of a data item x, any successive read operation on x by that process will always return that same value or a more recent value.|
    |Monotonic Writes|A write operation by a process on a data item x is completed before any successive write operation on x by the same process.|
    |Read your writes|The effect of a write operation by a process on data item x will always be seen by a successive read operation on x by the same process.|

???+note "Push vs. Pull protocols"
    In push protocols, the client opens a connection to the server and keeps it constantly active. The server will send (push) all new events to the client using that single always-on connection. In other words, the server PUSHes the new events to the client.
    
    In pull protocols, the client periodically connects to the server, checks for and gets (pulls) recent events and then closes the connection and disconnects from the server. The client repeats this whole procedure to get updated about new events. In this mode, the clients periodically PULLs the new events from the server.    




???+note ""
    * Primary-based protocols
        * reomte-Write protocols
        * local-write protocols
    * Replicated Write protocols
        * Active replication: require a process for each replica, that can perform the update on it.
        * Quorum-based protocols: $V_r+V_w>V$ $V_w > V/2$


???+note "RPC Server crash solution"
    Wait until the server reboots and try the operation again.

    Give up immediately and report black failure. 

    Guarantee nothing.

???+note "Client crash solutions"
    Before send an RPC, make a log Entry

    Divide time up into sequentially numbered epochs. When a client reboots, it brocasts ameesage declaring the start of a new epoch. When broadcast comes, all remote computations are killed.

    Each RPC is given a standard amout of time.


???+note "Advantage of Dynamic Binding"
    Flexibility

    Can support multiple servers that support the same interface

    The binder can verify that both client and server are using the same version of the interface

???+note "Disadvantages of Dynamic binding"
    Extra overhead of exporting/importing interfaces

    The binder may become a bottleneck in alarge distributed system    

???+note "Transient/Persistent Messaging"
    Transient: The sender puts the message on the net and id it cannot be delivered to the sender or to the next communication host, it is lost

    Persistent: The message is stored in the communication syatems





