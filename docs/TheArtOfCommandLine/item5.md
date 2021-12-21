???+note "`xargs`"
    `xargs` takes the data coming in on its standard input, splits it up, and uses it to run the command given in its arguments. By default, it splits on blanks or newlines,

???+info "`find` + `xargs`"
    `find . -name “*.b” | xargs rm -rf` This command will delete all file suffixed with `.b` in the current directory.

    `find . -type f -not -name '*gz' -print0 | xargs -0 -I {} rm -v {}` This shows how to delete all files within a directory except one or few files with a given extension. The `-0` option instructs `xargs` to split its input on null bytes instead of blanks or newlines. Combined with find's `-print0`, this allows filenames containing blanks or newlines to be handled properly. The `-I` option changes the way the new command lines are built. Instead of adding as many arguments as possible at a time, xargs will take one name at a time from its input, look for the given token ({} here) and replace that with the name.
    so the output shows here

    ```bash
    LearningCS ±|master|→ find . -mindepth 1 -maxdepth 1 -print0 | xargs -0I{} echo {}
    ./requirements.txt
    ./.DS_Store
    ./update.sh
    ./.github
    ./README.md
    ./.git
    ./mkdocs.yml
    ./docs
    ./.vscode
    ./LICENSE
    ```
