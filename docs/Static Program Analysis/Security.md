???+note "Concept of information flow security"
    Tracks how information flows through the program to make sure that the program handles the information securely. Concerns how information is propagated.


???+note "Confidentiality and integrity"
    |||||
    |-|-|-|-|
    |Confidentiality|Prevent secret information from being leaked|<img src="../img/P17.png" alt="l" style="width:500px;"/>||
    |Integrity|Prevent untrusted information from corrupting (trusted) critical information|<img src="../img/P18.png" alt="l" style="width:500px;"/>|Command injection,SQL injection,XSS attacks|
    




???+note "Explicit flows and covert channels"

    Explicit flow: information flows through direct copying.

    Channels that exploit a mechanism whose primary purpose is not information transfer are called covert channels


???+note "Use taint analysis to detect unwanted information flow"
    Taint analysis tracks how tainted data flow through the program and observes if they can flow to locations of interest (called sinks). In practice, sinks are usually some sensitive methods.
    
    <img src="../img/P19.png" alt="l" style="width:400px;"/>