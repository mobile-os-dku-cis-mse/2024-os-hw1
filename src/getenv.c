#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_env(char **env_variables) {
    char *env = NULL;

    for (int i = 1; env_variables[i] != NULL; i++) {
        env = getenv(env_variables[i]);
        printf("%s=%s\n", env_variables[i], env);
        for (int j = 0; ; j++) {
            env = strtok_r(env, ":", &env);
            if (env == NULL) break;
            printf("\t%s\n", env);
        }
        printf("***---------------------***\n");
    }
    return 0;
}