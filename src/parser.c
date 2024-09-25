#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "process.h"

static bool is_in_path(char *command)
{
    char *path = getenv("PATH");

    return true;
}

static bool is_valid_command(char *command)
{
    if (strcmp(command, "exit") == 0 || is_in_path(command))
        return true;
    return false;
}

int main_loop()
{
    char *line = NULL;
    char *pwd = NULL;
    size_t linecap = 0;
    ssize_t linelen = 0;
    int callback = 0;

    while (callback == 0) {
        if ((pwd = getenv("PWD")) == NULL)
            return 84;
        printf("-> %s ", pwd);
        if ((linelen = getline(&line, &linecap, stdin)) == -1) {
            if (errno == EINTR) {
                errno = 0;
                continue;
            }
            return 0;
        }
        line[linelen - 1] = '\0';
        if (is_valid_command(line))
            callback = process_command(line);
        else
            printf("shell: command not found: %s\n", line);
    }
    return 0;
}
