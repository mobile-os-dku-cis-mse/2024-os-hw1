#include "word_arrays.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void change_working_directory(char *arg)
{
    char *pwd = NULL;
    char *path = NULL;

    pwd = getcwd(pwd, 42);
    if (pwd == NULL) {
        perror("Couldn't get pwd: ");
        return;
    }
    path = malloc(sizeof(char) * (strlen(pwd) + strlen(arg) + 2));
    strcpy(path, pwd);
    path[strlen(pwd)] = '/';
    path[strlen(pwd) + 1] = '\0';
    strcat(path, arg);
    if (chdir(path) == -1) {
        fprintf(stderr, "cd: no such file or directory: %s\n", arg);
        free(path);
        return;
    }
    free(pwd);
    pwd = NULL;
    if (strcmp(arg, "..") != 0) {
        if (setenv("PWD", path, 1) == -1)
            perror("Couldn't change PWD env variable: ");
    } else {
        pwd = getcwd(pwd, 42);
        if (setenv("PWD", pwd, 1) == -1)
            perror("Couldn't change PWD env variable: ");
        free(pwd);
    }
    free(path);
}

void set_working_directory_to_home()
{
    char *home_path = getenv("HOME");

    if (home_path == NULL) {
        fprintf(stderr, "Couldn't find HOME env variable\n");
        return;
    }
    if (chdir(home_path) == -1) {
        perror("Couldn't set working directory to HOME: ");
        return;
    }
    if (setenv("PWD", home_path, 1) == -1)
        perror("Couldn't set PWD env variable to HOME: ");
}

int cd_command(char *command)
{
    char **argv = str_to_word_array(command, ' ');
    size_t argc = boardlen(argv);

    if (argc > 2)
        fprintf(stderr, "cd: string not in pwd: %s\n", argv[1]);
    else if (argc == 1)
        set_working_directory_to_home();
    else
        change_working_directory(argv[1]);
    free_board(argv);
    return 0;
}
