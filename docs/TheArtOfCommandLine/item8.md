???+note "Know the various signals you can send processes."
    There are many ways to send signals to processes. 

    1. Use `kill` command to send a signal to a process. For example, you can suspend a process by `suspend a process`

    2.  Use the UNIX system call kill (from a C program) to send signal from one process to another.
    ```bash
    int send_signal (int pid)
    {
            int ret;
            ret = kill(pid,SIGHUP);
            printf("ret : %d",ret);

    }
    ```

    3. When a process is running on the terminal, you can send signal to that process from the keyboard by using some specific combination of keys. Pressing `Ctrl + C` kills the running foreground process. 
