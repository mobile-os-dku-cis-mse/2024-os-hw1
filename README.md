# os_hw1 SiSH
## Introduction

This is a simple shell program that can execute commands in the PATH environment variable.\
Once executed, the shell will display a prompt and wait for the user to enter a command.\
The shell will then execute the command and display the output to the user.

## Features

- Execute commands in the PATH environment variable
- Display a prompt for the user to enter a command
- Display the output of the command to the user
- Exit the shell by typing 'exit' or 'quit' or pressing Ctrl-D
- Display an error message if the command is not found
- getenv function to get the environment varaibles passed as arguments

## Build

To build the program, run the following command:

```bash
make
```

This will create an executable file called `SiSH`.

## Run

To run the program, execute the following command:

```bash
./SiSH
```

This will start the shell and display a prompt for the user to enter a command.

## Usage

Once executed the shell will display a `> ` prompt for the user to enter a command.\
To execute a command, type the command with its arguments and press Enter.\
The shell will then execute the command and display the output to the user.

## Exit

To exit the shell, type 'exit' or 'quit' or press Ctrl-D.

## Clean

To clean up the build files, run the following command:

```bash
make clean
```

This will remove the object files.

In order to also remove the executable file, run the following command:

```bash
make fclean
```

This will remove the object files and the executable file.

To rebuild the executable file from scratch, run the following command:

```bash
make re
```

This will remove the object files and the executable file, and then rebuild the executable file.