//
// Created by hochacha on 24. 9. 28.
//

#include "path_finder.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH_MAX 2048

char* bin_path_finder(char* bin) {
    char* path = getenv("PATH");
    if (path == NULL) {
        printf("PATH env variable not found\n");
        return NULL;
    }

    char* path_dup = strdup(path);
    if (path_dup == NULL) {
        printf("strdup failed\n");
        return NULL;
    }

    char* dir = strtok(path_dup, ":");
    while (dir != NULL) {
        char full_path[PATH_MAX] = {0};
        snprintf(full_path, PATH_MAX, "%s/%s", dir, bin);

        if (access(full_path, X_OK) == 0) {
            free(path_dup);
            // full_path is allocated in stack, so make it in heap
            return strdup(full_path);
        }

        dir = strtok(NULL, ":");
    }

    printf("Program %s not found in PATH.\n", bin);
    free(path_dup);
    return NULL;
}

char* file_path_finder(const char* filename) {
    char* resolved_path = malloc(PATH_MAX);
    if (resolved_path == NULL) {
        perror("file_path_finder: memory allocation failed");
        return NULL;
    }

    if (realpath(filename, resolved_path) == NULL) {
        if (errno == ENOENT) {
            char* last_slash = strrchr(filename, '/');
            if (last_slash != NULL) {
                *last_slash = '\0';
                if (realpath(filename, resolved_path) != NULL) {
                    *last_slash = '/';
                    strcat(resolved_path, last_slash);
                } else {
                    free(resolved_path);
                    return NULL;
                }
            } else {
                if (getcwd(resolved_path, PATH_MAX) == NULL) {
                    free(resolved_path);
                    return NULL;
                }
                strcat(resolved_path, "/");
                strcat(resolved_path, filename);
            }
        } else {
            free(resolved_path);
            return NULL;
        }
    }

    return resolved_path;
}

void file_path_prefixer(char* args[], int arg_count) {
    for (int i = 1; i < arg_count; i++) {
        if(args[i][0] == '-') {
            continue;
        }

        if (strncmp(args[i], "./", 2) == 0 || strncmp(args[i], "../", 3) == 0) {
            char* new_path = file_path_finder(args[i]);
            if (new_path != NULL) {
                free(args[i]);
                args[i] = new_path;
            }
        }
    }
}