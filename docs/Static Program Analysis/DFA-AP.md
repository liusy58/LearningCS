???+note "Understand the three data flow analyses"  

    - reaching definitions

    A definition d at program point p reaches a point q if there is a path from p to q such that d is not “killed” along that path. That's to say, definition of variable v at program point p reaches point q if there is a path from p to q such that no new definition of v appears on that path. Reaching definitions can be used to detect possible undefined variables.

    <img src="../img/reachable.png" alt="l" style="width:500px;"/>

    - live variables

    Live variables analysis tells whether the value of variable v at program point p could be used along some path in CFG starting at p. If so, v is live at p; otherwise, v is dead at p.


    <img src="../img/live.png" alt="l" style="width:500px;"/>

    - available expressions

    An expression x op y is available at program point p if (1) allpaths from the entry to p mustpass through the evaluation of x op y, and (2) after the last evaluation of x op y, there is no redefinition of x or y

???+note "Can tell the differences and similarities of the three data flow analyses" 
    ||Type|Transfer Function|Control Flow|Algorithm|
    |-|-|-|-|-|
    |Reaching Definition Analysis|may analysis<img src="../img/P1.png" alt="l" style="width:500px;"/>|<img src="../img/RDTF.png" alt="l" style="width:500px;"/>|<img src="../img/CF.png" alt="l" style="width:500px;"/>|<img src="../img/algorithm1.png" alt="l" style="width:500px;"/>|
    |Live Variables Analysis|<img src="../img/P2.png" alt="l" style="width:500px;"/>||||


    


???+note "Understand the iterative algorithm and can tell why it is able to terminate"
    Set of facts is finite. 

