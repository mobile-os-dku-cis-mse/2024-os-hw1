#include <string.h>
#include <stdio.h>

int process_command(char *command)
{
    if (strcmp(command, "exit") == 0)
        return 1;
    printf("command %s processed\n", command);
    return 0;
}
