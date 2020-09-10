# ReadMe - Assignment 2 - Creating an Interactive User Defined Shell

## For Question 1:

To compile: ```make```

To run: ```./main```

Important points to note before running the program:
 - Buffer size is set to be 4096 Bytes.
 - For history to work, shell needs to have read write permissions on the root directory.
 - ```headers.h``` contains the references to inbuilt header files.
 - ```generics.c``` consists of custom functions to ease working with commonly used operations like trim(), strcat(), etc.
 - Time Complexity for a majority of custom functions in generics.h: ```O(n)```

Some assumptions:
 - The program has been tested on WSL 2 based Ubuntu terminal (running on Windows 10) and thus has commands parsing values based on the data format of ```/proc/{pid}/{status, etc.}``` in this machine.
 - The directory from where the shell is launched will be set as the root directory for the shell.
 - It is assumed that background process logic should only work on commands executed by execvp() since other commands are custom and execute instantly.
 - The substring of path containing the address to the root directory will be replaced by ```~```.

## Machine Specifications
 - **Operating System:** 64 bit Windows 10 Home running WSL 2 
 - **Terminal:** Microsoft Windows Subsystem for Linux Launcher
 - **Processor:** Intel Core i7-8750H CPU @ 2.20 GHz 2.21 GHz
 - **RAM:** 16 GB

## About me
 - **Name:** Shlok Pandey
 - **Roll Number:** 2020121008
 - **Email Id:** shlok.pandey@research.iiit.ac.in