#### 4.2.1 POSIX Process Creation and Destruction

???+note "primitives"
    |Name|Definition|
    |-|-|
    |`fork()`|Create a process.|
    |`kill()`|Kill a process.|
    |`exit()`|Destroy a process.|
    |`wait()`|Wait on its children.|
    

???+info "Processes Created Via fork() Do Not Share Memory"
    ```C++
    int x = 0;
    int main(int argc, char *argv[])
    {
        int pid;
        pid = fork();
        if (pid == 0) { /* child */
            x = 1;
            printf("Child process set x=1\n");
            exit(EXIT_SUCCESS);
        }
        if (pid < 0) { /* parent, upon error */
            perror("fork");
            exit(EXIT_FAILURE);
        }
         /* parent */
         waitall();
         printf("Parent process sees x=%d\n", x);
         return EXIT_SUCCESS;
    }
    ```



#### 4.2.2 POSIX Thread Creation and Destruction

???+note "note"
    |||
    |-|-|
    |`pthread_create()`|Create a thread within an existing process.|
    |`pthread_exit()`||


???+info "Threads Created Via pthread_create() Share Memory"
    ```C++
    1 int x = 0;
    2
    3 void *mythread(void *arg)
    4 {
    5 x = 1;
    6 printf("Child process set x=1\n");
    7 return NULL;
    8 }
    9
    10 int main(int argc, char *argv[])
    11 {
    12 int en;
    13 pthread_t tid;
    14 void *vp;
    15
    16 if ((en = pthread_create(&tid, NULL,
    17 mythread, NULL)) != 0) {
    18 fprintf(stderr, "pthread_create: %s\n", strerror(en));
    19 exit(EXIT_FAILURE);
    20 }
    21
    22 /* parent */
    23
    24 if ((en = pthread_join(tid, &vp)) != 0) {
    25 fprintf(stderr, "pthread_join: %s\n", strerror(en));
    26 exit(EXIT_FAILURE);
    27 }
    28 printf("Parent process sees x=%d\n", x);
    29
    30 return EXIT_SUCCESS;
    31 }
    ```  

#### 4.2.3 POSIX Locking

???+note "primitives"
    |||
    |-|-|
    |`pthread_mutex_lock()`|"acquires" the specified lock|
    |`pthread_mutex_unlock()`|"releases” the specified lock. |
    |`pthread_mutex_init()`||
    |`PTHREAD_MUTEX_INITIALIZER`||



    