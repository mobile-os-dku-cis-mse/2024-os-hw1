#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

// Function to startup information
void startup_shell(char **user, char **pwd) {
    printf("\n\n");

    // user name
    *user = getenv("USER");
    if (*user == NULL) {
        *user = "unknown"; 
    }

    printf("User: %s\n", *user);

    // real time
    time_t current_time = time(NULL);
    struct tm *local_time = localtime(&current_time);

    printf("Time: %02d:%02d:%02d\n", local_time->tm_hour, local_time->tm_min, local_time->tm_sec);

    // Path
    *pwd = getenv("PWD");
    if (*pwd == NULL) {
        printf("Unable to get PWD environment variable.\n");
    } else {
        printf("Path: %s\n\n", *pwd);
    }

    printf("Welcome MyShell!\n\n\n");
}

// Function to remove quotes from a string
void remove_quotes(char *arg) {
    char *src = arg, *dst = arg;
    while (*src) {
        if (*src != '"' && *src != '\'') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0'; // Null-terminate the modified string
}


// Function to split the command into arguments
int parse_command(char *cmd, char **args) {
    int count = 0;
    char *token = strtok(cmd, " \n");
    while (token != NULL && count < MAX_ARGS - 1) {
        remove_quotes(token);
        args[count++] = token;
        token = strtok(NULL, " \n");
    }
    args[count] = NULL; // Null-terminate the argument list
    return count;
}

// Function to execute the command
void execute_command(char **args, char **pwd) {
    if (args[0] == NULL) {
        return; // No command entered
    }

    // Check for 'cd' command
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else {
            // Attempt to change directory
            if (chdir(args[1]) != 0) {
                perror("cd failed");
                printf("\n");
            } else {
                // Update the current working directory
                char *new_pwd = getcwd(NULL, 0);
                if (new_pwd != NULL) {
                    // Only free the previous `pwd` if it was dynamically allocated (i.e., by `getcwd()`)
                    if (*pwd != getenv("PWD")) {
                        free(*pwd);
                    }
                    *pwd = new_pwd; // Update pwd
                } else {
                    perror("getcwd failed");
                }
            }
        }
        return; // Do not fork a new process
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        printf("\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        if (execvp(args[0], args) == -1) {
            perror("exec failed");
            printf("\n");
            exit(EXIT_FAILURE);
        }
    } else { // Parent process
        int status;
        waitpid(pid, &status, 0); // Wait for child to complete
    }
}
