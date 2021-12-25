???+note "logical clocks"
    A logical clock is a mechanism for capturing chronological and causal relationships in a distributed system. Distributed systems may have no physically synchronous global clock, so a logical clock allows global ordering on events from different processes in such systems.



### Lamport’s logical clocks
???+note "Lamport’s logical clocks"
    For Lamport’s logical clocks, each process maintains a local counter $C_i$. These counters are updated according to the following steps:

    1. Before executing an event, $P_i$ increments $C_i$ : $C_i <- C_i + 1$

    2. When process Pi sends a message m to process $P_j$, it sets m’s timestamp ts(m) equal to $C_i$ after having executed the previous step.

    3. Upon the receipt of a message m, process $P_j$ adjusts its own local counter as $C_j$ ← max { $C_j$ , ts(m)} after which it then executes the first step and delivers the message to the application.


### Example: Total-ordered multicasting
// need to read more 


### Vector clocks

???+note "vector clocks"
    A vector clock is a data structure used for determining the partial ordering of events in a distributed system and detecting causality violations.



