???+note "Concept of context sensitivity (C.S.)"
    Context sensitivity models calling contexts by distinguishing different data flows of different contexts to improve precision


???+note "Concept of context-sensitive heap (C.S. heap)"
    The most common choice is to inherit contexts from the method where the object is allocated



???+note "Why C.S. and C.S. heap improve precision"
    In dynamic execution, an allocation site can create multiple objects under different calling contexts, different objects (allocated by the same site) may be manipulated with different data flows, e.g., stored different values to their fields. In pointer analysis, analyzing such code without heap contexts may lose precision by merging the data flows of different contexts to one abstract object.In contrast, distinguishing different objects from the same allocation site by heap contexts gains precision.



???+note "Context-sensitive pointer analysis rules"
    <img src="../img/CSRules.png" alt="l" style="width:500px;"/>






???+note "Algorithm for context-sensitive pointer analysis"
    <img src="../img/CSalg.png" alt="l" style="width:500px;"/>

    



???+note "Common context sensitivity variants"
    Call-site sensitivity
    <img src="../img/P41.png" alt="l" style="width:500px;"/>

    Object sensitivity
    <img src="../img/P42.png" alt="l" style="width:500px;"/>

    Type Sensitivity
    <img src="../img/P43.png" alt="l" style="width:500px;"/>







???+note "Differences and relationship among common context sensitivity variants"
    In practice, object sensitivity generally outperforms  call-site sensitivity for OO languages (like Java)

    Under the same k-limiting, the precision of type sensitivity is no better than object sensitivity

    


