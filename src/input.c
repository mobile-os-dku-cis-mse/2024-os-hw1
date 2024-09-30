#include <stdio.h>
#include <string.h>
#include "sish.h"

int read_input(char *input_buffer) {
    printf("SiSH> ");
    if (fgets(input_buffer, MAX_INPUT_LENGTH, stdin) == NULL) {
        if (feof(stdin)) {
            return -1;
        }
        perror("fgets failed");
        return -1;
    }

    size_t length = strlen(input_buffer);
    if (input_buffer[length - 1] == '\n') {
        input_buffer[length - 1] = '\0';
    }

    return 0;
}
