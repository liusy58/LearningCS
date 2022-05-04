## 1. Introduction  


### 1.1 What do compilers do?

Compilers do two things: the first is just to translate one language to another that hardware can actually execute. The second is to improve the code.

#### 1.1.1 why we need to learn compiler optimizations?

=== "reasons"

    1. I's important to consider when {==designing hardware==} what compiler can do well and what compiler cannot do well.
    2. For people who interested in {==programming languages==}, it is also important to know what can be optimized successfully anb less successfully when you are deciding what to put into a new language. This has become a very hot topic these days when we have a lot of new languages designed for specific programming environment such as AI application, data-intensive computing. 
    3. There are a lot of {==innovation in hardware==} in terms of delivering potential performance like GPU, accelerators, etc. We need to make compilers take advantage of those things.


### 1.2 How can the compiler Improve performance? 
=== ""

    1. Minimize the number of operations.
    2. Replace expensive operations with simpler ones. For example, multiplication operations are fundamentally slower than shift operations. 
    3. Minimize cache misses. When speaking of expensive operations, one common thing is accessing memory, in morden archtecture, we have a cache hierarchy for optimization. But cache miss can be very costly. So doing things to make cache mpre effective is also very im portant.
    4. Perform work in parallel. Another thing we can do is to harness all of the parallel hardware such as GPUs which  have thousands of parallel processing elements in them. Here we want to both be doing the work with a thread efficiently (instruction scheduling) and we want to generate work that can take multiple threads. 


### 1.3 Structure of a Compiler


In fact, you can just hardwire for the particular type of source code and that particular target just like you do in compiler intro class. But it's a real lack of portability. 


<img src="images/llvm_compiler_pipeline.png" alt="l" style="width:300px;"/> 


### 1.4 Ingredients in a compiler optimization 