#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int get_env(char **env_variables);

int execute_command(char input[]) {
    int (*fun_ptr[])(char **) = {
        get_env
    };
    char **args = malloc(sizeof(char *) * 1024);
    char *arg = NULL;
    int i = 0;

    arg = strtok(input, " ");
    while (arg != NULL) {
        args[i] = strdup(arg);
        i++;
        arg = strtok(NULL, " ");
    }
    args[i - 1][strlen(args[i - 1]) - 1] = '\0';
    args[i] = NULL;
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        if (strcmp(args[0], "getenv") == 0) {
            (*fun_ptr[0])(args);
        } else {
            execvp(args[0], args);
        }
        return 0;
    } else {
        wait(NULL);
    }
    for (int j = 0; args[j] != NULL; j++) {
        free(args[j]);
    }
    free(args);
    return 0;
}

int exec_command(char input[]) {
    char *command = malloc(sizeof(char) * 1024);
    char *arg = NULL;
    char **args = malloc(sizeof(char *) * 1024);
    int i = 0;

    command = strtok(input, " ");
    while ((arg = strtok(NULL, " ")) != NULL) {
        args[i] = strdup(arg);
        i++;
    }
    args[i] = NULL;
    if (i > 0) {
        args[i - 1][strlen(args[i - 1]) - 1] = '\0';
        command[strlen(command)] = '\0';
    } else {
        command[strlen(command) - 1] = '\0';
        args[0] = NULL;
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        printf("Executing %s\n", command);
        printf("Arguments:\n");
        for (int j = 0; args[j] != NULL; j++) {
            printf("%s\n", args[j]);
        }
        execvp(command, args);
        return 0;
    } else {
        wait(NULL);
    }
    free(args);
    return 0;
}
