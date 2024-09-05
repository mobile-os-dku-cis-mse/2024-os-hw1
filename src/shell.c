#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "commands/getenv.h"
#include "commands/quit.h"

typedef void (*command_func_ptr)(char **args);

void execute_command(char **args) {
    if (args[0] == NULL) {
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Failed to fork");
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("Command execution failed");
            exit(EXIT_FAILURE);
        }
    } else {
        wait(NULL);
    }
}

typedef struct {
    char *name;
    command_func_ptr func;
} Command;

Command command_table[] = {
    {"getenv", getenv_command},
    {"quit", quit_command},
    {NULL, execute_command}
};

// Function to split the input into arguments
char **parse_input(char *input) {
    char **args = malloc(64 * sizeof(char *));
    if (!args) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    char *token;
    int position = 0;
    token = strtok(input, " ");
    while (token != NULL) {
        args[position] = token;
        position++;

        if (position >= 64) {
            args = realloc(args, (position + 1) * sizeof(char *));
            if (!args) {
                perror("Failed to reallocate memory");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " ");
    }
    args[position] = NULL;
    return args;
}

void process_command(char *input) {
    char **args = parse_input(input);

    for (int i = 0; command_table[i].name != NULL; i++) {
        if (strcmp(args[0], command_table[i].name) == 0) {
            command_table[i].func(args + 1);
            free(args);
            return;
        }
    }

    execute_command(args);
    free(args);
}