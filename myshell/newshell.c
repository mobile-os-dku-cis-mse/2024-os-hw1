#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include "other_func.h"

void (*old_fun)( int);

void read_command(char *command){
    printf("symoon$ ");
    fgets(command, 4095, stdin);
    command[strcspn(command, "\n")] = 0; // \n 제거하기

    /*
    fgets, gets, fgets: 전부 뒤에 \0 붙음
    fgets: \n도 같이 저장, 공백 입력 가능 
    scanf, gets: \n이 붙지 않음
    */
}

// signal function : ctrl-c 강제종료 없애기
void ctrlc_handler( int signo) {
    char c; // 사용자 입력받을 문자 선언

    printf("\nDo you really want to quit? [y/n]"); // 사용자 입력 묻는 프린트문    
    

    c = getchar(); // 문자 입력받기
    if (c == 'y' || c == 'Y') { // c가 y혹은 Y이면 종료하기
        exit(0);
    } else {
        // 버퍼 비우기 (by. ChatGPT)
        // while ((c = getchar()) != '\n' && c != EOF) { }
        printf("Enter\n");
        // 아니면 계속 진행되기
        }
}

void help_command() { // 명령어를 help해주는 함수
    printf("***---------------------***\n");
    printf("Command different from the original:\n");
    printf("exit\t: Exit the shell.\n");
    printf("help\t: Show this help\n");
    printf("&\t: background processing\n");
    printf("cd\t: Change the current directory.\n");
    printf("env\t: Get environment value.\n");
    printf("***---------------------***\n");
	
}


void print_command(char *command){
    pid_t pid = fork(); // 자식 프로세스 생성

    if(pid == 0){ // 성공
        char* argv[100];
        char* token = strtok(command, " ");
        int i = 0;
        while(token != NULL){
            argv[i++] = token;
            token = strtok(NULL, " ");
        }
        argv[i] = NULL;

        if(strcmp(argv[0], "env") == 0){
            echo_getenv(i, argv);
        } else {
            execvp(argv[0], argv); // 명령어 실행 
            perror("execve failed");
            printf("If you are curious about other commands, check out \'help\'.\n");
        }
        exit(1);
        

    } else if(pid > 0) {
        wait(NULL);
    } else {
        perror("Fork Failed");
    }

    

}

int main(){
    char command[4095];
    
    // ctrl + c를 사용하여 강제종료되지 않도록 함
    signal(SIGINT, ctrlc_handler); 
    while(1){

        // 명령어 읽기
        read_command(command);

        if(strcmp(command, "quit") == 0) {
            printf("symoon shell is terminated...\n");
            break; // "exit" 입력 시, 종료
        }
        else if(strcmp(command, "help") == 0){
            help_command();
        }
        else if(strncmp(command, "cd ", 3) == 0){
            cd_command(command);
        }
        else print_command(command);
    }

    return 0;
}