#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#define MAX_CMD 8
#define MAX_CWD 200

void tokenize_command(char *command_copy, char *command[])
{
    char *checkpoint;
    char *token = strtok_r(command_copy, " ", &checkpoint);
    int loop_counter = 0;
    for(; loop_counter < MAX_CMD && token != NULL; loop_counter++)
    {
        command[loop_counter] = token;
        token = strtok_r(NULL, " ", &checkpoint);
    }
    command[loop_counter] = NULL;
}

void search_command(char *path_copy, char path_buffer[], int limit, char *command[], bool *found)
{
    char *checkpoint;
    char *path_dir = strtok_r(path_copy, ":", &checkpoint);
    struct stat stat_ret;
    while (path_dir != NULL)
    {
        // * Construct the path (add "/" between the directory and the command (executable file))
        snprintf(path_buffer, limit, "%s/%s", path_dir, command[0]);

        // * Check if there is a match, if the match is a regular file, and if the match is an executable file
        if (stat(path_buffer, &stat_ret) == 0 && S_ISREG(stat_ret.st_mode) && (stat_ret.st_mode & S_IXUSR))
        {
            *found = true;
            free(path_copy);
            break;
        }

        // * Move to the next directory
        path_dir = strtok_r(NULL, ":", &checkpoint);
    }
}

void print_shell_prompt()
{
    char cwd_buffer[MAX_CWD];
    char *directory = getcwd(cwd_buffer, sizeof(cwd_buffer));
    char *user = getenv("USER");

    struct timeval tv;
    struct timezone tz;
    struct tm *current_time;

    gettimeofday(&tv, &tz);

    current_time = localtime(&tv.tv_sec);

    printf("%s %s %02d:%02d:%02d ", user, directory, current_time->tm_hour, current_time->tm_min, current_time->tm_sec);
}