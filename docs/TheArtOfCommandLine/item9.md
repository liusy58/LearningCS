???+note "Use `nohup` or `disown` if you want a background process to keep running forever"
    `&` puts the job in the background, that is, makes it block on attempting to read input, and makes the shell not wait for its completion.

    `disown` removes the process from the shell's job control, but it still leaves it connected to the terminal. One of the results is that the shell won't send it a `SIGHUP`. Obviously, it can only be applied to background jobs, because you cannot enter it when a foreground job is running.
    
    `nohup` disconnects the process from the terminal, redirects its output to nohup.out and shields it from SIGHUP. One of the effects (the naming one) is that the process won't receive any sent SIGHUP. It is completely independent from job control and could in principle be used also for foreground jobs (although that's not very useful).

