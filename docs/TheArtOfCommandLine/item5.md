???+note "`xargs`"
    `xargs` reads streams of data from standard input, then generates and executes command lines; meaning it can take output of a command and passes it as argument of another command.

???+info "`find` + `xargs`"
    `find . -name “*.b” | xargs rm -rf` This command will delete all file suffixed with `.b` in the current directory.

    `find . -type f -not -name '*gz' -print0 | xargs -0 -I {} rm -v {}` This shows how to delete all files within a directory except one or few files with a given extension.
