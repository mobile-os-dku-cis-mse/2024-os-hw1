#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "process.h"
#include "word_arrays.h"

int parser_loop(char **env)
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
        callback = process_command(line, env);
    }
    return 0;
}
