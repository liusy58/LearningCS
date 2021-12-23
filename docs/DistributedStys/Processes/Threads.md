


### Thread implementation

???+note 
    Threads are often provided in the form of a thread package in user space or in kernel space. 

???+info "Advantage of user-level thread"
    1. cheap to create and destroy threads (only need to allocate memory to set up a thread stack)

    2. cheap in context switch (few ubstructions)

???+info "LWP"



### Threads in distributed systems

#### Multithreaded clients


#### Multithreaded servers

???+info "Three ways to construct a server"
    |Model|Character|Advantage|Disadvantage|
    |-|-|-|-|
    |Multithreading|Parallelism, blocking system calls|easy for programming and allow for parallelism||
    |Single-threaded process|No parallelism, blocking system calls|simple and easy to program|hinder performance|
    |Finite-state machine|Parallelism, nonblocking system calls|achieves high performance|hard to program|

