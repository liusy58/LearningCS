
### Using Dataflow Analysis to detect Memory Leaks

#### Part A Detecting Memory Leaks

A memory leak occurs when memory is allocated but never deallocated after its last use. This can waste memory resource in a long-running program. Detecting memory bugs is difficult because of aliases where multiple variables may point to the same location. 

We eliminate the complexity of this problem with the following simplified instruction set (p is a pointer variable and `v` is a scalar non-pointer variable in the program):

* 1. `p = alloc()`; allocate a block of memory and assign its pointer to p.
* 2. `*p = v`; write the scalar (non-pointer) value `v` to the location p. (Note that the value `v` is scalar, i.e. not a pointer.)
* 3. `v = *p`; the read version of the above instruction (again, `v` couldn’t be a pointer).
* 4. `free(p)`; deallocate the block of memory pointed to by `p`.


To simplify the problem, please assume that no pointer arithmetic will happen, and that we can only assign a pointer with the alloc() instruction.

Your task is to warn programmers about any potential memory leaks in the program.

You may treat each instruction as a basic block.

(1) Please describe the possible conditions of memory leaks (hint: there are two possible types).

(2) Define a data flow analysis to solve this problem by filling out the table below.

(3) Specify how you use the data flow results to issue a warning on each potential memory leak.

There are other errors like use-after-free and deleting unallocated memory, but ignore these errors in Part A.

|||
|-|-|
|Direction of your analysis (forward/backward)||
|Lattice elements and meaning||
|Meet operator or lattice diagram||
|Is there a top element? If yes, what is it?||
|Is there a bottom element? If yes, what is it?||
|Transfer function of a basic block||
|Boundary condition initialization||
|Interior points initialization||


