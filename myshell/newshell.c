#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include "other_func.h"

#define MAX_HISTORY 200
#define MAX_COMMAND_LENGTH 1024
struct termios orig_termios; // 화살표 입력키 위한 termios 제어


void read_command(char *command){
    char now_path[200];
    getcwd(now_path, sizeof(now_path));
    printf("\033[90m~%s\033[0m$ ", now_path);
    fgets(command, MAX_COMMAND_LENGTH, stdin);
    command[strcspn(command, "\n")] = 0; // \n 제거하기
    // history[history_count++] = command;
    
    /*
    fgets, gets, fgets: 전부 뒤에 \0 붙음
    fgets: \n도 같이 저장, 공백 입력 가능 
    scanf, gets: \n이 붙지 않음
    */
}

// signal function : ctrl-c 강제종료 없애기
void ctrlc_handler(int signo) {
    // Ctrl+C가 눌렸을 때 처리할 내용
    // printf("\nEnter: Caught signal %d\n", signo);
    printf("\nIf you want to quit, Enter \'quit\'.\n");
}

void help_command() { // 명령어를 help해주는 함수
    printf("***---------------------***\n");
    printf("Command different from the original:\n");
    printf(" - quit\t: Exit the shell.\n");
    printf(" - help\t: Show this help.\n");
    printf(" - cd\t: Change the current directory.\n");
    printf(" - env\t: Get environment value.\n");
    printf(" - |\t: Pipe output of one command to the input of another command.\n");
    printf("***---------------------***\n");
}

void execute_command(char *command) {
    if (strchr(command, '|') != NULL) {
        fork_command_with_pipe(command); // 파이프가 있을 때
    } else {
        fork_command(command); // 파이프가 없을 때
    }
}


int main(){
    char command[MAX_COMMAND_LENGTH];
    
    // ctrl + c를 사용하여 강제종료되지 않도록 함
    signal(SIGINT, ctrlc_handler); 

    while(1){
        // 명령어 읽기
        char username[] = "symoon:";
        printf("\033[36m%s", username);
        read_command(command);

        if(strcmp(command, "quit") == 0 || strcmp(command, "q") == 0 || strcmp(command, "Quit") == 0) {
            printf("symoon shell is terminated...\n");
            break; // "quit" 입력 시, 종료
        }
        else if(strcmp(command, "help") == 0){
            help_command();
        }
        else if(strncmp(command, "cd ", 3) == 0){
            cd_command(command);
        }
        else execute_command(command);
    }

    return 0;
}