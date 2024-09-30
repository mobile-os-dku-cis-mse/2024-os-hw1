#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sish.h"

char **get_paths() {
    char *env_path = getenv("PATH");
    if (!env_path) {
        fprintf(stderr, "PATH environment variable not found.\n");
        return NULL;
    }

    char **paths = malloc(MAX_PATHS * sizeof(char *));
    if (!paths) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(env_path, ":");
    int index = 0;
    while (token != NULL && index < MAX_PATHS) {
        paths[index++] = strdup(token);
        token = strtok(NULL, ":");
    }
    paths[index] = NULL;

    return paths;
}

char *find_executable(char **paths, const char *command) {
    static char full_path[MAX_INPUT_LENGTH];

    for (int i = 0; paths[i] != NULL; i++) {
        snprintf(full_path, sizeof(full_path), "%s/%s", paths[i], command);
        if (access(full_path, X_OK) == 0) {
            return full_path;
        }
    }
    return NULL;
}
