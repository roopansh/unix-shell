# UNIX-SHELL
IIT Guwahati, India : CS-341 Assignment task - Make a UNIX Shell with some basic functionalities.

## Implemented Functions
#### ``` > cd [path]```
  Changes the current working directory to the path specified.

#### ``` > ls```
Lists all the files/directories present in the current working directory.

#### ``` > rm [-r] [-f] [-v] [file/dir]```
Removes the specified files. Use the ```-r``` flag to remove a directory.
```-v``` flag displays the filename which is deleted.

#### ``` > rmexcept [[file1] [file2]....]```
Removes all the files in the current directory except the spefied files.

**NOTE:- It doesn't delete the directories in the current directory.**

#### ``` > history [n]```
Displays the n recent commands on the screen. If n is not spefied, then all the commands are displayed.

#### ``` > exit```
Leaves the terminal
