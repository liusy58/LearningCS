???+note "Understand CFL-Reachability"
    A path is considered to connect two nodes A and B, or B is reachablefrom A, only if the concatenation of the labels on the edges of the pathis a word in a specified context-free language.


???+note "Understand the basic idea of IFDS"
    IFDS is for interprocedural data flow analysiswith distributive flow functions over finite domains.

???+note "Understand what problems can be solved by IFDS"
    Given a statement S, besides S itself, if we need to consider multiple input data facts to create correct outputs, then the analysis is not distributive and should not be expressed in IFDS.

    In IFDS, each data fact (circle) and its propagation (edges) could be handled independently, and doing so will not affect the correctness of the final results.