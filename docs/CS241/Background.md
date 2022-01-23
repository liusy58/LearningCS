### Systems Architecture

#### Assembly 


#### Atomic Operations

???+note "atomic operation"
    An operation is atomic if no other processor should interrupt it. If an instruction is atomic, it makes sure that only one processor or thread performs any intermediate step at a time. 


#### Hyperthreading

???+note "hyperthreading"
    Hyperthreading allows one physical core to appear as many virtual cores to the operating system.  

    [How I found a bug in Intel Skylake processors](http://gallium.inria.fr/blog/intel-skylake-bug/)



### Debugging and Environments

#### ssh

???+note "ssh"
    `ssh` is short for secure shell. It is a network protocol that allows you to spawn a shell on the remote machine. You can use `ssh-copy-id` to skip repeating typing your password every time you use ssh. The config file resides in `~/.ssh/config`. 

#### git

???+note "git"
    Git is a version control system that stores the entire history of a directory. 

#### clean code


=== "midify_before.cpp"

    ```cpp
    void selection_sort(int *a, long len){
        for(long i = len-1; i > 0; --i){
            long max_index = i;
            for(long j = len-1; j >= 0; --j){
                if(a[max_index] < a[j]){
                    max_index = j;
                }
            }
            int temp = a[i];
            a[i] = a[max_index];
            a[max_index] = temp;
        }

    }
    ```

=== "midify_after.cpp"

    ```cpp
    long max_index(int *a, long start, long end);
    void swap(int *a, long idx1, long idx2);
    void selection_sort(int *a, long len);
    ```

Make sure that your function does one thing so you need write some helper functions. An example is shown before.


#### Valgrind  

???+note "introduction"
    Valgrind is a suite of tools designed to provide debugging and profiling tools to make your programs more correct and detect some runtime issues. To run valgrind on your program:

    ```bash
    valgrind --leak-check=full --show-leak-kinds=all myprogram arg1 arg2
    ```


#### TSAN 

???+note "ThreadSanitizer"
    ThreadSanitizer is a tool from Google, built into clang and gcc, to help you detect race conditions in your code. You can compile code by `gcc -fsanitize=thread -pie -fPIC -ltsan -g simple_race.c`


### GDB

#### Shell

???+note "introduction"
    A shell is a programming language that is runnint inside your terminal. A terminal is merely a window to input commands.



#### Undefined Behavior Sanitizer

The [undefined behavior sanitizer](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html) is a wonderful tool provided by the llvm project.

Read [Chris Lattner’s 3 Part blog post on undefined behavior](http://blog.llvm.org/2011/05/what-every-c-programmer-should-know.html). 


#### Clang Static Build Tools

Clang provides a great drop-in replacement tools for compiling programs. If you want to see if there is an error that may cause a race condition, casting error, etc, all you need to do is the following.

```bash
$ scan-build make
```

#### strace and ltrace

???+note "Introduction"
    strace and ltrace are two programs that trace the system calls and library calls respectively of a running program or command. 

=== "ltrace_test.cpp"

    ```cpp
    int main() {
        FILE *fp = fopen("I don't exist", "r");
        fprintf(fp, "a");
        fclose(fp);
        return 0;
    }
    ```

=== "Use ltrace"

    ```bash
    > ltrace ./a.out
    __libc_start_main(0x8048454, 1, 0xbfc19db4, 0x80484c0, 0x8048530 <unfinished ...>
    fopen("I don't exist", "r")                          = 0x0
    fwrite("Invalid Write\n", 1, 14, 0x0 <unfinished ...>
    --- SIGSEGV (Segmentation fault) ---
    +++ killed by SIGSEGV +++
    ```