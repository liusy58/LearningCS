### The art of Command line

Here I will give detailed examples of the command introduced in the [repo](https://github.com/jlevy/the-art-of-command-line/blob/master/README.md).

This is a very good repo that I think every programmer need to master every item mentioned in it.

* Use `pgrep` and `pkill` to find or signal processes by name (`-f` is helpful)
 
`pgrep` is a command-line utility that allows you to find the process IDs of a running program based on the given criteria.Here I give some examples of how to use it.


???+note 
    use `-l` option to show the process name along with its ID:
    ```bash
    ## example 1:
    ## use -l option to show the process name along with its ID:
    pgrep -l "ssh"

    ```

