#include <stdio.h>
#include <stdlib.h>

void getenv_command(char **args) {
    if (args[0] == NULL) {
        printf("Usage: getenv <variable_name>\n");
        return;
    }

    char *env_value = getenv(args[0]);
    if (env_value) {
        printf("%s\n", env_value);
    } else {
        printf("Environment variable not found.\n");
    }
}
