# ReadMe - B30-Shell

This is a custom implementation of Unix Bash shell in C. It supports input-output redirection, piping, background processes, signal handling, multiple commands per line, environment variables and custom commands implemented in C.

## Instructions

To compile: ```make```

To run: ```./main```

Important points to note before running the program:
 - Buffer size is set to be 4096 Bytes.
 - For history to work, shell needs to have read write permissions on the root directory.
 - ```headers.h``` contains the references to inbuilt header files.
 - ```generics.c``` consists of custom functions to ease working with commonly used operations like trim(), strcat(), etc.
 - Since more than two states are possible, but in the question it was mentioned that states should be either running or stopped. Hence, status code for "T (stopped)", "Z (zombie)", and "X (dead)" os assumed to be in stopped state, while rest are in running state.
 - Time Complexity for a majority of custom functions in generics.h: ```O(n)```

Some assumptions:
 - The program has been tested on WSL 2 based Ubuntu terminal (running on Windows 10) and thus has commands parsing values based on the data format of ```/proc/{pid}/{status, etc.}``` in this machine.
 - The directory from where the shell is launched will be set as the root directory for the shell.
 - It is assumed that background process logic should only work on commands executed by execvp() since other commands are custom and execute instantly.
 - The substring of path containing the address to the root directory will be replaced by ```~```.
 - The path should not contain any spaces.

## File information

- **cd.c** :  Implementation of cd program.
- **childproc.c** : Consists of functions to generate, add, delete and get nodes from the linked list of background process.
- **cleanup.c** : Consists of procedures to be followed while quitting the shell, which includes ending background processes and freeing up memory.
- **definitions.h** : Definition of structure for procDetails.
- **echo.c** : Implementation of echo program with " " handling.
- **envvar.c** : Consists of functions for setting, unsetting and getting environment variables.
- **execute.c** : Consists of methods to deal with execution of processes associated with the shell using fork. Background process are also handled here
- **fgbg.c** : Consists of methods to bring background process to foreground and to start a stopped background process
- **generics.c** : Consists of custom methods which makes the work easier. Custom methods include: getHostName(), getCurrentUser(), trim(), concat(), substr(), getBaseName(), rootPathResolve(), split().
- **globals.c** : Consists of global variables and their getters and setters. These global variables are used throughout the shell.
- **headers.h** : Definitions of all the inbuilt headers is present in this file. This also includes constant declarations.
- **history.c** : Functions to save and view history of commands are present in this file.
- **init.c** : Consists of signal handlers and initialisation functions for global variables. Triggered only once, ie when the shell starts.
- **jobs.c** : Consists of methods to deal with background process. This includes jobs(), kjob(), overkill().
- **log.txt**: Data for the history of the shell is stored here.
- **ls.c** : Implementation of ls program.
- **main.c** : Starting point of the shell. Triggers a loop, displays a prompt, and proceeds with further required methods.
- **makefile** : Consists of command to compile multiple c files together into one file, and cleans output files.
- **pinfo.c** : Consists of functions to get details about any process based on its process id.
- **prompt.c** : Displays username, hostname and pathname before getting input command.
- **pwd.c** : Implementation of pwd program.
- **shellinput.c** : Consists of methods to take input, trim whitespace, split the command(based on pipe, input output redirection and spaces), and execute it based on the command name.

## Machine Specifications
 - **Operating System:** 64 bit Windows 10 Home running WSL 2 
 - **Terminal:** Microsoft Windows Subsystem for Linux Launcher
 - **Processor:** Intel Core i7-8750H CPU @ 2.20 GHz 2.21 GHz
 - **RAM:** 16 GB