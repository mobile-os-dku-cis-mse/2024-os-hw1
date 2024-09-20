#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int pids[10];
int count;
int flag = 0;

#define MAX_LINE 80

int main() {
    char * args[MAX_LINE / 2 + 1];
    char input[MAX_LINE];
    int should_run = 1;

    // running SiSH Script
    while (should_run){
        printf("SiSH> ");
        fflush(stdout);

        fgets(input, MAX_LINE, stdin);

        if((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
            input[strlen(input) - 1] = '\0';


        if(strcmp(input, "exit") == 0){
            should_run = 0;
            continue;
        }

        int i = 0;
        args[i] = strtok(input, " ");
        while(args[i] != NULL){
            i++;
            args[i] = strtok(NULL, " ");
        }

        pid_t pid = fork();

        if(pid < 0){
            fprintf(stderr, "fail to execute\n");
            return 1;
        } else if(pid == 0){
            if(execvp(args[0], args) == -1){
                // execvp의 반환 값에 따라서, 명령 실패 이유를 찾도록 한다.
                fprintf(stderr, "fail to run the command\n");
                return 0;
            }
        } else {
            wait(NULL);
        }
    }
    return 0;
}
