# UNIX-SHELL
IIT Guwahati, India : CS-341 Assignment task - Make a UNIX Shell with some basic functionalities.

## How to Run
    $ gcc main.c
    $ ./a.out
    
    > <command-to-run>
    
    
## Implemented Built-in Functions
#### ```> help```
Displays the list of in-built functionalities.

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
Displays the 'n' recent commands on the screen. If n is not spefied, then all the commands are displayed.

#### ``` > issue n```
Runs the n-th command again. Use the ```history``` command  to check the number of the command.

#### ``` > program_name [< input_file] [> output_file] [--tkill n]```
This will run the specified program. It supports the redirection operators ```> output_file``` and ```< input_file```.
**Note :- ```--tkill n``` is used to specify the time(in seconds) after which the program is terminated irrespective of whether the execution of child thread is completed or not.**

#### ``` > exit```
Exits the terminal.

## Special Note 
1) Implemented all the features asked in the question statement.
2) Every command of the user is run as a separate thread forked by the main thread.
3) The memory used by history of commands is allocated dynamically in chunks of 10 commands. This is memory effecient and stores the complete history.
4) Each command given as input by the user also uses dynamic memory allocation in chunks of 1024 characters.
5) The code is completely modular. It is very effecient to read and understand with all the comments.

## Bugs
There are no bugs.

## Project Authors
    Abhishek Goyal
    Roll No - 150101002
    IIT Guwahati (CSE)


    Rohan Aggarwal
    Roll No - 150101052
    IIT Guwahati (CSE)


    Roopansh Bansal
    Roll No - 150101053
    IIT Guwahati (CSE)

**Contribution of Each member :- Each member of the group was present during the sessions and everyone contributed together as a team to the project.**
