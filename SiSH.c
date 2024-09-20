#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 100

void execute_command(char *input) {
    char *args[MAX_ARG_SIZE];
    char *token;
    int i = 0;
    
    // Tokenize the input string
    token = strtok(input, " \n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL; // Null-terminate the argument list

    // If the user types "quit", exit the shell
    if (strcmp(args[0], "quit") == 0) {
        exit(0);
    }

    // Handle 'cd' command
    if (strcmp(args[0], "cd") == 0) {
        if (i < 2) {
            fprintf(stderr, "cd: missing argument\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd failed");
            }
        }
        return; // Return to avoid forking
    }

    // Handle 'make' command
    if (strcmp(args[0], "make") == 0) {
        if (i < 2) {
            fprintf(stderr, "make: missing argument\n");
            return;
        }
        
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            return;
        } else if (pid == 0) { // Child process
            // Prepare the command to compile the C file
            char *compiler_args[] = {"gcc", args[1], "-o", "a.out", NULL}; // Change "output" to desired output filename
            execvp("gcc", compiler_args); // Execute gcc
            perror("Compilation failed"); // If execvp fails
            exit(1);
        } else { // Parent process
            wait(NULL); // Wait for the child to finish
        }
        return; // Return after handling make
    }

    // Check if the command is an executable file starting with './'
    if (strncmp(args[0], "./", 2) == 0) {
        pid_t pid = fork(); // Create a new child process to execute
        if (pid < 0) {
            perror("Fork failed");
            return;
        } else if (pid == 0) { // Child process for executing
            execvp(args[0], args); // Execute the specified executable
            perror("Execution failed"); // If execvp fails
            exit(1);
        } else { // Parent process
            wait(NULL); // Wait for the execution to finish
        }
        return; // Return after executing the command
    }

    // Fork a child process for other commands
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return;
    } else if (pid == 0) { // Child process
        // Get the PATH environment variable
        char *path = getenv("PATH");
        char *path_token = strtok(path, ":");
        char command_path[MAX_INPUT_SIZE];

        // Try to find the command in the directories listed in PATH
        while (path_token != NULL) {
            snprintf(command_path, sizeof(command_path), "%s/%s", path_token, args[0]);
            execve(command_path, args, NULL); // Execute the command
            path_token = strtok(NULL, ":"); // Move to the next directory
        }

        // If execve fails
        perror("Command execution failed");
        exit(1); // Exit child process with error
    } else { // Parent process
        wait(NULL); // Wait for the child to finish
    }
}

int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        printf("SiSH >>> "); // Prompt
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("Failed to read input");
            continue;
        }

        // Execute the command
        execute_command(input);
    }

    return 0;
}

/*
execve는 환경 변수를 명시적으로 제공할 수 있지만, execvp는 환경 변수를 기본적으로 현재 프로세스의 환경을 사용
*/