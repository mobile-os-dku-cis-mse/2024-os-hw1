#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "functions.h"
#define MAX_BUFF 100
#define MAX_CMD 8
#define MAX_PATH 200

int main()
{
    char command_buffer[MAX_BUFF]; // * A buffer to keep the current command
    char *command[MAX_CMD]; // * A buffer to keep tokens (words in an command)
    char path_buffer[MAX_PATH]; // * A buffer to contain the path directory to be compared to the command

    // * A loop to keep receiving commands until a 'quit' command is received.
    while(1)
    {
        // * Receive command
        print_shell_prompt();
        fgets(command_buffer, sizeof(command_buffer), stdin);
        char *command_copy = strdup(command_buffer);
        printf("\n");

        // * Remove the endline character from input if available (for strcmp)
        command_copy[strcspn(command_buffer, "\n")] = 0;

        // * Check if the command is a 'quit' command
        if (strcmp(command_copy, "quit") == 0)
        {
            printf("Shell terminated.\n");
            exit(EXIT_SUCCESS);
        }

        // * Tokenize command
        tokenize_command(command_copy, command);

        // * Get PATH environment variable (list of locations in the filesystem)
        char *path_var = getenv("PATH");
        if(path_var == NULL)
        {
            perror("PATH not found.\n");
            exit(EXIT_FAILURE);
        }

        // * Look for the directory containing the command
        bool found = false;
        char *path_copy = strdup(path_var);
        search_command(path_copy, path_buffer, MAX_PATH, command, &found);
        
        // * Handle the command without forking if it's cd
        if(!strcmp(command[0], "cd")) 
        {
            if(!chdir(command[1]))
            {
                setenv("PWD", command[1], 1); // * Overwrite the PWD environment variable
            }
            else perror("Returned an error");
            continue;
        }

        // * Command found 
        if(found)
        {
            // printf("Path to command: %s\n", path_buffer);
            char *args[] = {path_buffer, command[1], command[2], command[3], command[4], command[5], command[6], command[7], NULL};
            // printf("args is ");
            // for(int i = 0; (i > MAX_CMD) | (args[i] != NULL); i++)
            // {
            //     printf("%s ", args[i]);
            // }
            // printf("\n\n");


            // * Create child process
            pid_t pid = fork();
            int status;
            if(pid > 0) // * Parent process
            {
                wait(&status); // * Wait until child process terminates       
            }
            else if (pid == 0) // * Child process
            {
                // * Execute the input command
                if(!execve(path_buffer, args, NULL))
                {
                    perror("Returned an error");
                }
                else execve(path_buffer, args, NULL);
            }
            else 
            {
                perror("Fork failed.\n");
                exit(EXIT_FAILURE);
            }
        }
        else perror("Command not found.\n");
    }
    return 0;
}