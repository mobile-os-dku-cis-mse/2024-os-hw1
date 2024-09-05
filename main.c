#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "src/shell.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

int main(int argc, char **argv) {
    if (argc != 1)
        return 84;

    char *command = NULL;
    char *res = NULL;

    while (1) {
        char buffer[1024] = {0};
        free(command);
        command = NULL;

        printf("> ");
        res = fgets(buffer, 1024, stdin);

        if (res == NULL)
            exit (0);

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strlen(buffer) == 0) {
            continue;
        }

        command = strdup(buffer);
        if (!command) {
            perror("Failed to allocate memory");
            return 1;
        }

        process_command(command);
    }

    return 0;
}
