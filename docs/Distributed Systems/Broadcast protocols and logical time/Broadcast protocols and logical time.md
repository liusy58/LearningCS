???+note "logical vs. physical clocks"
    It cannot be guranteened by the physical time that if a->b, time(a) is less than time(b).

    Logical clocks focus on correctly capturing the order of events in a distributed system.


???+note "Lamport clocks algorithm"

    <img src="../img/lamportclock.png" alt="l" style="width:500px;"/>

    
    Using Lamport timestamps we can extend this partial order into a total order.


???+note "vector clocks"
    Given the Lamport timestamps of two events, it is in general not possible to tell whether those events are concurrent or whether one happened before the other.


### Delivery order in broadcast protocols

???+note "How to achieve fault tolerance in replication"
    ||||
    |-|-|-|
    |Read-afet-write consistency|||
    
