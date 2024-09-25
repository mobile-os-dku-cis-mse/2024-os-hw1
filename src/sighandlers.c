#include <stdio.h>
#include <stdlib.h>

void sighandler_int(int sig)
{
    if (sig != SIGINT)
        exit(EXIT_FAILURE);
    printf("\n");
}
