???+note "fault tolerance "
    A distributed system needs to be fault-tolerant, which means that whenever a failure occurs, the system should continue to operate in an acceptable way.

### Basic concepts

???+note "Requirements for a dependable system"
    Being fault-tolerant is strongly re4lated to what are called dependable systems. There is a need to see the requirements for a dependable system.

    |Requirement|Definition|
    |-|-|
    |Availability|It refers to the property that the system is operating correctly **at any given moment**.|
    |Reliability|It refers to the property that a system is operating correctly **during a time interval**.|
    |Safety|It refers to the situation that when a system temporarily fails to operate correctly, no catastrophic event happens.|
    |Maintainability|It refers to how easily a failed system can be repaired.|

???+note "fault vs. error vs. failure" 
    A fault causes an error and an error results in a failure. 


### Failure models


### Failure masking by redundancy

???+note "How to improve dependability?"
    |Type of redundancy|Definition|
    |-|-|
    |Information redundancy|Extra bits are added to allow recovery from garbled bits. (eg. hamming code)|
    |Time redundancy|An action is performed, and then, if need be, it is performed again. (TCP)|
    |Physical Redundancy|Extra equipment or processes are added to make it possible for the system as a whole to tolerate the loss or malfunctioning of some components.|  



