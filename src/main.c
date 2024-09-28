#include <stdio.h>
#include <signal.h>
#include "sighandlers.h"
#include "parser.h"

int main(__attribute__((unused)) int argc, __attribute__((unused))
    char **argv, char **env)
{
    struct sigaction sa;

    sa.sa_handler = sighandler_int;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    parser_loop(env);
    printf("exit\n");
    return 0;
}
