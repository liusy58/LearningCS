### Virtualization and distributed systems


???+note "Why distributed systems need virtualization?"
    1.  portability is greatly improved as virtual machines provide a further decoupling between hardware and software, allowing a complete environment to be moved from one machine to another.

    2. Imporatnt in the context of reliability and security for (distributed) systems as it  allows for the isolation of a complete application and its environment, a failure caused by an error or security attack need no longer affect a complete machine.



### Types of virtualization

???+note "Three different types of virtualization"
    |Type|Characteristic|Advantage||
    |-|-|-|-|
    |A process virtual machine| Virtualization is only for a single process|| <img src="../img/03-08a.png" alt="l" style="width:200px;"/> |
    |A native virtual machine monitor| Interface offered by a virtual machine monitor can be offered simultaneously to different programs|Different guest operating systems can run independently and concurrently on the same platform.|<img src="../img/03-08b.png" alt="l" style="width:200px;"/>|
    |A hosted virtual machine monitor|Make use of existing facilities provided by that host operating system|Easy to implement|<img src="../img/03-08c.png" alt="l" style="width:200px;"/>|

    


### Application of virtual machines to distributed systems

???+note "Three different types service provided by cloud"
    |Service|Characteristic|
    |-|-|
    |Infrastructure-as-a-Service (IaaS)| covering the basic infrastructure|
    |Platform-as-a-Service (PaaS)|covering system-level services|
    |Software-as-a-Service (SaaS)|containing actual applications|

    <img src="../img/saas-vs-paas-vs-iaas.png" alt="l" style="width:300px;"/>
    <img src="../img/cloud-service-models-iaas-paas-saas-stackscale.jpg" alt="l" style="width:300px;"/>

Virtualization plays a key role in IaaS. Instead of renting out a physical machine, a cloud provider will rent out a virtual machine (monitor) that may, or may not, be sharing a physical machine with other customers. 