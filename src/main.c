#include <stdio.h>
#include <signal.h>
#include "sighandlers.h"
#include "parser.h"

int main(void)
{
    struct sigaction sa;

    sa.sa_handler = sighandler_int;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    main_loop();
    printf("exit\n");
    return 0;
}
