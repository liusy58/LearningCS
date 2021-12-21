???+note "`pgrep` and  'pkill'"
    Use `pgrep` and `pkill` to find or signal processes by name (`-f` is helpful)

    `pgrep` is a command-line utility that allows you to find the process IDs of a running program based on the given criteria.

???+info "examples"
    ```bash
    use `-l` option to show the process name along with its ID:
    ## example 1:
    pgrep -l "ssh"
    ```    