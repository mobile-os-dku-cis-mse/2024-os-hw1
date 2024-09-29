#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void tokenize_command(char *command_copy, char *command[]);
void search_command(char *path_copy, char path_buffer[], int limit, char *command[], bool *found);
void print_shell_prompt();

#endif