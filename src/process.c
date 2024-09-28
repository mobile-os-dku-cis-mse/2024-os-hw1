#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include "word_arrays.h"

int execute_programme(char *command, char **env)
{
    pid_t child_pid = fork();
    int wstatus = 0;
    char **argv = str_to_word_array(command, ' ');

    if (child_pid == -1)
        return 84;
    if (child_pid == 0) {
        execve(argv[0], argv, env);
        exit(84);
    } else {
        waitpid(child_pid, &wstatus, 0);
        if (WEXITSTATUS(wstatus) == 84) {
            fprintf(stderr, "shell: no such file or directory: %s\n", argv[0]);
        }
    }
    return 0;
}

char *allocate_path(char *command, char *path)
{
    size_t length = strlen(command) + strlen(path) + 2;
    char *dest = malloc(sizeof(char) * length);

    if (dest == NULL)
        return NULL;
    strcpy(dest, path);
    dest[strlen(path)] = '/';
    dest[strlen(path) + 1] = '\0';
    dest = strcat(dest, command);
    dest[strlen(command) + strlen(path) + 1] = '\0';
    return dest;
}

void find_path(char **argv, char **env)
{
    char *path = NULL;
    char *paths_list = getenv("PATH");
    char **paths_board = NULL;

    if (paths_list == NULL)
        exit(84);
    paths_board = str_to_word_array(paths_list, ':');
    for (size_t i = 0; paths_board[i] != NULL; i++) {
        path = allocate_path(argv[0], paths_board[i]);
        if (path == NULL)
            exit(84);
        execve(path, argv, env);
        free(path);
    }
    exit(84);
}

int execute_command(char *command, char **env)
{
    pid_t child_pid = fork();
    int wstatus = 0;
    char **argv = str_to_word_array(command, ' ');

    if (child_pid == -1)
        return 84;
    if (child_pid == 0) {
        find_path(argv, env);
    } else {
        waitpid(child_pid, &wstatus, 0);
        if (WEXITSTATUS(wstatus) == 84) {
            fprintf(stderr, "shell: command not found: %s\n", argv[0]);
        }
    }
    return 0;
}

int process_command(char *command, char **env)
{
    if (strcmp(command, "quit") == 0)
        return 1;
    if (strncmp(command, "./", 2) == 0)
        return execute_programme(command, env);
    if (execute_command(command, env) == 84)
        perror("error while executing command: ");
    return 0;
}
