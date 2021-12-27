???+note "Why distributed systems need clock?"
    |||
    |-|-|
    |Schedulers, timeouts, failure detectors, retry timers|timeout-based failure detectors need to measure time to determine when a timeout has elapsed.|
    |Performance measurements, statistics, profiling||
    |Log files & databases|record when an event occurred|


???+note "Two types of clock"
    |Type|Definition|
    |-|-|
    |Physical clocks|count number of seconds elapsed|
    |Logical clocks|count events|

### Clock synchronisation and monotonic clocks


### Causality and happens-before

???+note "happens-before relation"
    Happens-before relation is a relation between the result of two events, such that if one event should happen before another event.
