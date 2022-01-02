???+note "Concept of information flow security"
    if the information in variable x is transferred to variable y, then there is information flow x → y  

???+note "Confidentiality and integrity"
    Confidentiality: Prevent secret information from being leaked

    Integrity: Prevent untrusted information from corrupting (trusted) critical information



???+note "Explicit flows and covert channels"
    Explicit flow:information flows through direct copying.

    Channels that exploit a mechanism whose primary purpose is not information transfer are called covert channels


???+note "Use taint analysis to detect unwanted information flow"
    Taint analysis tracks how tainted data flow through the program and observes if they can flow to locations of interest (called sinks). In practice, sinks are usually some sensitive methods.