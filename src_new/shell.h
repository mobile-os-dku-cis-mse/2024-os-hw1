#ifndef SISH_H
#define SISH_H

#define HOST_NAME_MAX 40
#define HOST_MAX 40
#include <sys/types.h>

typedef struct _system_caller{
    char* host;
    char hostname[HOST_NAME_MAX];
    uid_t uid;
}shell_runner;

int run_shell();
#endif //SISH_H
