#ifndef SISH_H
#define SISH_H

#define MAX_INPUT_LENGTH 1024
#define MAX_PATHS 100

char **get_paths(void);
char *find_executable(char **paths, const char *command);
void execute_command(char *command, char **argv);
int read_input(char *input_buffer);

#endif