???+info "Is there a simpler way to create a parallel shell script? If so, how? If not, why not?"
    One straightforward approach is the shell pipeline 

    `grep $pattern1 | sed -e 's/a/b/' | sort`

    For a sufficiently large intput file, `grep` will patternmatch in parallel with `sed` editing and with the input processing of `sort`

???+info "But if script-based parallel programming is so easy, why bother with anything else?"
    In fact, it is likely that a very large fraction of parallel programs in use today are script-based. However, script-based parallelism does have its limitations: 
    
    1. Creation of new processes is usually quite heavy-weight, involving the expensive `fork()` and `exec()` system calls. 

    2. Sharing of data, including pipelining, typically involves expensive file I/O. 

    3. The reliable synchronization primitives available to scripts also involves expensive file I/O. 

    4. Scripting languages are often too slow, but are often quite useful when coordinating execution of long-running programs written in lower-level program languages.

    These limitations require that script-based parallelism use coarse-grained parallelism, with each unit of work having execution time of at least tens of milliseconds, and perferably much longer. 