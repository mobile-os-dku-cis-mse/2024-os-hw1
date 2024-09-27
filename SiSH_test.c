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

    // Fork a child process for other commands
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return;
    } else if (pid == 0) { // Child process
        execvp(args[0], args);

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