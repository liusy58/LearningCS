???+info "bang mechanism"
    The VM handles stack overflow by framing the stack arena with inaccessible guard pages, and intercepting the accesses to those guard pages to detect the case where a stack overflow occurred. That also requires and additional logic of actually probing the stack when putting a new activation record on it: by touching the stack down trying to trigger the guard page fault. This mechanism has a fancy name of "stack banging", and if we want to do anything below stack pointer, we need to communicate the additional banging to the runtime.




## registers
???+note "number of registers"
    |||
    |-|-|
    |`rax`|0|
    |`rcx`|1|
    |`rdx`|2|
    |`rbx`|3|
    |`rsp`|4|
    |`rbp`|5|
    |`rsi`|6|
    |`rdi`|7|
    |`r8`|8|
    |`r9`|9|
    |`r10`|10|
    |`r11`|11|
    |`r12`|12|
    |`r13`|13|    
    |`r14`|14|
    |`r15`|15|



???+note "XMM registers"
    XMM registers are separate registers introduced with SSE(Data transfer Instructions) and still widely used nowadays. They are 128 bits wide, with instructions that can treat them as arrays of 64, 32(integer and floating point), 16 or 8 bit(integer only) values. You have 8 of them in 32 bit mode, 16 in 64 bit.




``` mermaid
classDiagram
  Person <|-- Student
  Person <|-- Professor
  Person : +String name
  Person : +String phoneNumber
  Person : +String emailAddress
  Person: +purchaseParkingPass()
  Address "1" <-- "0..1" Person:lives at
  class Student{
    +int studentNumber
    +int averageMark
    +isEligibleToEnrol()
    +getSeminarsTaken()
  }
  class Professor{
    +int salary
  }
  class Address{
    +String street
    +String city
    +String state
    +int postalCode
    +String country
    -validate()
    +outputAsLabel()  
  }
```



        