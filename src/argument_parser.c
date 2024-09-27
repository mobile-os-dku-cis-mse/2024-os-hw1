//
// Created by hochacha on 24. 9. 27.
//

#include "argument_parser.h"

#include <string.h>
#define MAX_ARGS 20

void argument_parser(char* input, char **args) {
    char* token;
    int i = 0;

    token = strtok(input, " ");
    while(token != NULL && i < MAX_ARGS - 1) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }

    args[i] = NULL;
}
