//
// Created by hochacha on 24. 9. 28.
//

#include "path_finder.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH_MAX 2048

int bin_path_finder(char* bin) {
    char* path = getenv("PATH");
    if(path == NULL) {
        printf("PATH env variable not found\n");
        return -1;
    }

    char *path_dup = strdup(path);
    if(path_dup == NULL) {
        printf("strdup failed\n");
    }

    char* dir = strtok(path_dup, ":");

    while(dir != NULL) {
        char full_path[PATH_MAX] = {0,};
        snprintf(full_path, PATH_MAX, "%s/%s", dir, bin);

        if(access(full_path, X_OK) == 0) {
            printf("Found: %s\n", full_path);
            free(path_dup);
            return 1;
        }

        dir = strtok(NULL, ":");
    }

    printf("Program %s not found in PATH.\n", bin);
    free(path_dup);

    return 0;
}

void path_finder(char*** args) {

}

