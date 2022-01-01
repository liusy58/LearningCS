???+note "How to build call graph via class hierarchy analysis"
    <img src="../img/CHA.png" alt="l" style="width:500px;"/>


???+note "Concept of interprocedural control-flow graph"
    An ICFG of a program consists of CFGs of the methods in the program, plus two kinds of additional edges:

    Call edges: from call sites to the entry nodes of their callees
    
    Return edges: from exit nodes of the callees to the  statements following their call sites (i.e., return sites)



???+note "Concept of interprocedural data-flow analysis"



???+note "Interprocedural constant propagation"

