### Virtualization and distributed systems


???+note "Why distributed systems need virtualization?"
    1.  Legacy software cannot be maintained in the same pace as the platforms it relies on

    2. Management becomes much easier if edge servers would support virtualization.


### Types of virtualization

???+note "Three different types of virtualization"
    |Type|Characteristic|Advantage|
    |-|-|-|
    |A process virtual machine| Virtualization is only for a single process||
    |A native virtual machine monitor| Interface offered by a virtual machine monitor can be offered simultaneously to different programs|different guest operating systems can run independently and concurrently on the same platform.|
    |A hosted virtual machine monitor|Make use of existing facilities provided by that host operating system|Easy to implement|

    <img src="img/03-08a.png" alt="drawing" style="width:300px;"/><img src="img/03-08b.png" alt="drawing" style="width:300px;"/><img src="img/03-08c.png" alt="drawing" style="width:300px;"/>

