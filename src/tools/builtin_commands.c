//
// Created by hochacha on 24. 9. 29.
//
#include "builtin_commands.h"

#ifndef MAX_ARGS 1024
#define MAX_ARGS 1024
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "path_finder.h"


int change_directory(char* arg[]) {
    if (arg[1] == NULL) {
        char* temp = getenv("HOME");
        if (temp == NULL) {
            fprintf(stderr, "PATH env is not set.\n");
            return -1;
        }
        arg[1] = temp;
    }

    arg[1] = file_path_finder(arg[1]);

    if (chdir(arg[1]) != 0) {
        perror("Fail to change directory: ");
        return -1;
    }
    return 0;
}

int echo(char* args[MAX_ARGS]) {
    int i = 1;
    while (args[i] != NULL) {
        printf("%s", args[i]);
        if (args[i + 1] != NULL) {
            printf(" ");
        }
        i++;
    }
    printf("\n");
    return 0;
}

