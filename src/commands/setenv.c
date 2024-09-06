//
// Created by beafowl on 9/6/24.
//

#include <stdlib.h>
#include <stdio.h>
#include "setenv.h"

void setenv_command(char **args) {
    if (args[0] == NULL || args[1] == NULL) {
        fprintf(stderr, "setenv: missing argument\n");
        return;
    }

    if (setenv(args[0], args[1], 1) == -1) {
        perror("setenv");
    }
}
