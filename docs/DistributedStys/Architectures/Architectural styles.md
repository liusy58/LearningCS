???+note "software architecture"
    The logical organization of a distributed system also means its software architecture.

### Layered architectures
???+note 
    The basic idea for the layered style is simple: components are organized in a layered fashion where a component at layer $L_j$ can make a downcall to a component at a lower-level layer $L_i$ (with i < j) and generally expects a response. Only in exceptional cases will an upcall be made to a higher-level component.

    <img src="img/02-01.png" alt="drawing" style="width:300px;"/>

    (a):shows a standard organization in which only downcalls to the next lower layer are made. This organization is commonly deployed in the case of network communication.

    (b): Consider, for example, an application A that makes use of a library $L_{OS}$ to interface to an operating system. At the same time, the application uses a specialized mathematical library $L_{math}$ that has been implemented by also making use of $L_{OS}$. In this case, referring to Figure 2.1(b), A is implemented at layer $N − 1$, $L_{math}$ at layer $N − 2$, and  $L_{OS}$ which is common to both of them, at layer $N − 3$.

    (c):A typical example is when an operating system signals the occurrence of an event, to which end it calls a user-defined operation for which an application had previously passed a reference (typically referred to as a handle).

####  Layered communication protocols

```python
from socket import *
s = socket(AF_INET, SOCK_STREAM)
(conn, addr) = s.accept()    # returns new socket and addr. client
while True:                  # forever
    data = conn.recv(1024)   # receive data from client
    if not data: break       # stop if client stopped
    conn.send(str(data)+"*") # return sent data plus an "*"
conn.close()                 # close the connection
```

```python
from socket import *
s = socket(AF_INET, SOCK_STREAM)           
s.connect((HOST, PORT))    # connect to server (block until accepted) # send some data
s.send(’Hello, world’)     # send some 
data = s.recv(1024)        # receive the response
print data                 # print the result
s.close()                  # close the connection

```


#### Application layering

???+note "Application layering"
    A large class of distributed applications is targeted toward supporting user or application access to databases, many people have advocated a distinc- tion between three logical levels, essentially following a layered architectural style:
    
    The application-interface level 
    
    The processing level
    
    The data level

    <img src="img/02-04.png" alt="drawing" style="width:300px;"/>

    As a first example, consider an Internet search engine. Ignoring all the ani- mated banners, images, and other fancy window dressing, the user interface of a search engine can be very simple: a user types in a string of keywords and is subsequently presented with a list of titles of Web pages. The back end is formed by a huge database of Web pages that have been prefetched and indexed. The core of the search engine is a program that transforms the user’s string of keywords into one or more database queries. It subsequently ranks the results into a list, and transforms that list into a series of HTML pages. This information retrieval part is typically placed at the processing level.


### Object-based and service-oriented architectures

???+note 
    In essence, each object corresponds to what we have defined as a component, and these components are connected through a procedure call mechanism.

    <img src="img/02-05.png" alt="drawing" style="width:300px;"/>

    Object-based architectures are attractive because they provide a natural way of encapsulating data (called an object’s state) and the operations that can be performed on that data (which are referred to as an object’s methods) into a single entity. 
