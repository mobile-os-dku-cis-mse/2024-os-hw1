#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sish.h"

int main() {
    char input[MAX_INPUT_LENGTH];
    char *argv[MAX_PATHS] = {NULL};

    char **path_dirs = get_paths();
    if (!path_dirs) {
        fprintf(stderr, "Failed to get PATH directories.\n");
        return EXIT_FAILURE;
    }

    while (1) {
        if (read_input(input) == -1) {
            break;
        }

        if (strcmp(input, "quit") == 0) {
            break;
        }
    
        char *token = strtok(input, " ");
        int arg_index = 0;
        while (token != NULL && arg_index < MAX_PATHS) {
            argv[arg_index++] = token;
            token = strtok(NULL, " ");
        }
        argv[arg_index] = NULL;

        if (argv[0] == NULL) {
            continue;
        }

        char *executable = find_executable(path_dirs, argv[0]);
        if (executable) {
            execute_command(executable, argv);
        } else {
            fprintf(stderr, "Command not found: %s\n", argv[0]);
        }
    }
}