#ifndef OTHER_FUNC_H
#define OTHER_FUNC_H

void execve_command(char *copyCommand, char **args, int i);
void fork_command_with_pipe(char *command);
void fork_command(char *command);
void cd_command(char *command);
void echo_getenv(int argc, char *argv[]);

#endif