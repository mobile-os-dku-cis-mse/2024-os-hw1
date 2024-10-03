#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_LINE 80  // max command
#define MAX_ARGS 10  // max arg

// execute command
void execute(char* command) {
    pid_t pid = fork();  
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // execute command (child)
        char* args[MAX_ARGS];
        char* token = strtok(command, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;  // null terminate the array of arguments
        // search for comman in path env variable
        char* path = getenv("PATH");
        char* dir = strtok(path, ":");
        char filepath[256];
        // check path dir
        while (dir != NULL) {
            snprintf(filepath, sizeof(filepath), "%s/%s", dir, args[0]);
            execv(filepath, args);  // execute attempt
            dir = strtok(NULL, ":");  // move to next dir
        }
        // execute from current dir
        snprintf(filepath, sizeof(filepath), "./%s", args[0]);
        execv(filepath, args);  // execute attempt
        // fail
        perror("Command execution failed");
        exit(1);
    }
    else {
        // wait for child to finish
        wait(NULL);
    }
}
int main() {
    char input[MAX_LINE];
    printf("SiSH Start : \n");
    printf("Type 'quit' to exit.\n");
    while (1) {
        printf("SiSH> ");  // prompt display
        fflush(stdout);
        // get input
        if (fgets(input, MAX_LINE, stdin) == NULL) {
            perror("Failed to read input");
            exit(1);
        }
        input[strcspn(input, "\n")] = 0;
        // quit command check
        if (strcmp(input, "quit") == 0) {
            break;  // Exit the shell
        }
        // execute
        execute(input);
    }
    printf("Exiting SiSH\n");
    return 0;
}
