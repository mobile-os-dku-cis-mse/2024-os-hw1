#ifndef SHELL_H
#define SHELL_H

#define MAX_CMD_LEN 1024
#define MAX_ARGS 100

// Function prototypes
void startup_shell(char **user, char **pwd);
int parse_command(char *cmd, char **args);
void execute_command(char **args, char **pwd);

#endif // SHELL_H
