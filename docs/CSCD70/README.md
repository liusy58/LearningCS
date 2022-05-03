

## Loops

### Definitions

#### Dominator

Node d {==dominates==} node n in agraph (d dom n) if every path from the start node to n goes through d. Dominators can be organized as a tree.

<img src="images/Dtree.png" alt="l" style="width:500px;"/> 


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


#### Finding Back Edges
Traverse edges in a depth-first search of the flow graph form a depth-first spanning tree. Then we categorize edges in graph into :

    - Advancing (A) edges: from ancestor to proper descendant

    - Cross (C) edges: from right to left
    
    - Retreating (R) edges: from descendant to ancestor (not necessarily proper)


Then for each retreating edge t->h, we will check if h is in t's dominator list. 


#### Constructing Natural Loops

The natural loop of a back edge is the smallest set of nodes that includes the head and tail of the back edge, and has no predecessors outside the set, except for the predecessors of the header.

##### Algorithm

- delete h from the flow graph
- find those nodes that can reach t

### Preheader
Optimizations often require code to be executed
once before the loop. So Create a preheader basic block for every loop.


<img src="images/preheader.png" alt="l" style="width:500px;"/> 


From an optimization perspective, not every cycle is a loop. 


## Static Single Assignment (SSA)


### What is SSA?

{==Static single assignment==} is an IR where every variable is assigned a value at most once in the program text.

$\Phi$ merges multiple definitions along multiple control paths into a single definition.


#### How do we choose which $x_i$ to use?

In fact, we don't really care, because we just need to use `mov` on each incoming edge.

<img src="images/phi.png" alt="l" style="width:300px;"/> 


### Why SSA?

SSA form makes use-def chains explicit in the IR, which in turn helps to simplify some optimizations.


### How to convert to SSA?

In fact, we can directly insert $\Phi$ functions for all live variables at each join point, but this is too costly, because there may be too many useless $\Phi$ functions inserted. See example below, $x_2 = \Phi(x_1,x_1)$ is totally useless and should be deleted.

<img src="images/exp1.png" alt="l" style="width:300px;"/> 


So how to get the minimal SSA?

=== "Algorithm"

    1. Place all $\Phi$.
    2. Rename all variables.


#### When Do We Insert $\Phi$?


