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
Make sure that your function does one thing so you need write some helper functions.



