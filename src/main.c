#include <stdio.h>
#include <string.h>

int execute_command(char input[]);

int main(void)
{
    int quit = 0;
    char input[1024] = {0};

    while (quit == 0) {
        printf("> ");
        if (fgets(input, 1024, stdin) == NULL || strcmp(input, "quit\n") == 0 || strcmp(input, "exit\n") == 0) {
            quit = 1;
        } else {
            execute_command(input);
        }
    }
    return 0;
}
