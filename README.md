# HW1: Simple MyShell (SiSH) - User Guide

## Introduction

SiSH (Simple Shell) is a small program that allows a user to execute commands on the operating system, similar to a traditional shell. It accepts commands as input, executes them, and waits for the next command once the execution is complete. This guide explains how to use SiSH and provides an overview of its basic functionality.

## Compilation

To compile the SiSH program, simply use the following command:

```bash
make
```
This will build the project and create the sish executable.

### Other Useful Makefile Rules:

* clean: Removes object files (.o files).
* fclean: Removes object files and the executable.
* re: Cleans everything and recompiles the project from scratch.
* debug: Compiles the program with debugging symbols.
* redebug: Cleans everything and recompiles with debugging symbols.
* tests_run: Compiles and runs the test suite.

## General Functionality

Starting the Shell
To start SiSH, run the compiled executable in your terminal:

```bash
./SiSH
```

Executing Commands
Once SiSH is running, it will wait for you to type a command. Enter the name of any executable program available on your system, for example:

```bash
user/home > ls
user/home > pwd
```

SiSH uses the PATH environment variable to locate programs, so you don’t need to provide the full path for programs in these directories.
Exiting the Shell
SiSH will terminate when you type the following command:

``` bash
user/home> quit
```

This command stops the shell and returns control to the normal terminal.
Process Management
For each entered command, SiSH creates a child process to execute the command. It waits for the child process to finish before prompting for a new command. During program execution, the shell remains inactive until the program completes.

## Example Usage

Here’s an example of a typical session with SiSH:
```bash
$ ./SiSH
/home/user > ls
Desktop Documents Downloads
/home/user > pwd
/home/user
/home/user > quit
exit
```

In this example, SiSH runs the ls command to list files in the directory, then pwd to print the current directory, and finally quit to exit the shell.

## Optional Features

* Custom Shell Prompt: You can modify the SiSH prompt to display information like the current directory or username using the getenv function.
* Passing Arguments: SiSH also supports passing arguments to an executable, similar to a regular terminal.
Conclusion
* Catching sigint signal and prints prompt again.
* Ends when receiving EOF
* Custom implimentation of the command cd that uses environement variables.

SiSH is a minimalist yet functional shell that allows you to execute commands like a normal terminal while exploring key concepts such as process creation and management in a Unix system.
