#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int main() {
    char cmd[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    char *user = NULL; // Declare user
    char *pwd = NULL;  // Declare pwd

    // Set up the shell prompt
    startup_shell(&user, &pwd);

    char *home = getenv("HOME");

    while (1) {
        // Print the prompt
        if (strncmp(pwd, home, strlen(home)) == 0) {
            // Replace home path with '~'
            printf("%s@SiSH: ~%s$ ", user, pwd + strlen(home));
        } else {
            printf("%s@SiSH: %s$ ", user, pwd);
        }
        
        // Get user input
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            break; // Exit on EOF
        }

        // Check for exit command
        if (strcmp(cmd, "quit\n") == 0) {
            break;
        }

        // Parse the command into arguments
        parse_command(cmd, args);

        // Execute the command
        execute_command(args, &pwd);
    }

    printf("Goodbye! MyShell!\n");
    return 0;
}
