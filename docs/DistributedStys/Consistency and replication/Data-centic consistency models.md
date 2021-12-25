???+note "Consistency model"
    A consistency model basically refers to the degree of consistency that should be maintained for the shared memory data.

### Continuous consistency



### Consistent ordering of operations

???+note 
    |Type|Definition||
    |-|-|-|
    |Sequential consistency|Given an execution history, could it have resulted from reordering concurrent operations such that the order of operations within a process is maintained.|||
    |Casual consistency|Writes that are potentially causally related must be seen by all processes in the same order. Concurrent writes may be seen in a different order on different machines.||  
    ||||  