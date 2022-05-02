

## Loops

### Definitions

#### Dominator

Node d {==dominates==} node n in agraph (d dom n) if every path from the start node to n goes through d. Dominators can be organized as a tree.

<img src="../images/Dtree.png" alt="l" style="width:500px;"/> 


#### Natural loops


A header dominates all nodes in the loop, and a back edge is an arc whose head dominates its tail. (tail -> head) The natural loop of a back edge is the smallest set of nodes that includes the head and tail of the back edge, and has no predecessors outside the set, except for the predecessors of the header. 


### Algorithm to find Natural Loops 

#### Finding Dominators

Use dataflow analysis framework to find Dominators.

|||
|-|-|
|Direction|forward|
|Values|Basic blocks|
|Meet operator|$\cap$|
|Top|all BBs|
|Bottom|Empty set|
|Boundary condition| $OUT(E) = E$|
|Initialization for internal nodes|$OUT(BB) = T$|
|Transfer function|$f(b) = {b} \cup (\cap_{p = pre(b)}OUT[p])$|


From an optimization perspective, not every cycle is a loop. 