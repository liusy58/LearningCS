???+note "What are the differences between static analysis and (dynamic) testing?"
    Static analysis is done without executing any of the code; dynamic analysis relies on studying how the code behaves during execution.


???+note "Understand soundness, completeness, false negatives, and false positives."
    <img src="../img/1.png" alt="l" style="width:500px;"/>


???+note "Why soundness is usually required by static analysis?"
    Soundness is critical to a collection of important (static-analysis) applications such as compiler optimization and program verification.


    Soundness is also preferable to other (static-analysis) applications for which soundness is not demanded, e.g., bug detection, as better soundness implies more bugs could be found.

???+note "How to understand abstraction and over-approximation?"    
    Abstraction: Model the problem?
    
    Over-approximation: Not miss any bug!

    

