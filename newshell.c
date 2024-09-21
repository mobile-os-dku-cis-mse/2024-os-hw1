#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

char *env; // 환경변수

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

void help_command() { // 명령어를 help해주는 함수

    printf("Different commands:\n");
    printf("exit\t: Exit the shell.\n");
    printf("help\t: show this help\n");
    printf("&\t: background processing\n");
    printf("cd\t: Change the current directory.\n");
	
}

//cd --> chdir
void cd_command(char *argv){
    // 현재 dir 주소 저장
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd));
    printf("%s -> ", cwd);

    // cd를 사용하여 주소 변환
    // chdir(argv);
    int ch = chdir(argv);
    if(ch == -1){
        fprintf(stderr, "working directory change error: %s\n", strerror(errno));
    } else {
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
    }
    // chdir(argv);
    // fchdir(getcwd(cwd, sizeof(cwd)));
}
//signal --> ctrl + C 누르면 꺼지는 이슈 방지


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
        
        if(strcmp(argv[0], "cd") == 0){
            cd_command(argv[1]);
        }
        else {
            execvp(argv[0], argv); // 명령어 실행
            perror("execve failed");
        }
        exit(1);

        // 실행 파일의 전체 경로를 찾기
        /*char path[1024];
        snprintf(path, sizeof(path), "/usr/bin/%s", argv[0]); // 경로

        // execve 사용: 실행 파일 경로, 인자 배열, 환경 변수 배열
        char *envp[] = { NULL }; // 환경 변수가 필요 없으면 NULL로 설정
        if (execve(path, argv, envp) == -1) {
            fprintf(stderr, "프로그램 실행 error: %s\n", strerror(errno));
            exit(1);
        }*/

    } else if(pid > 0) {
        wait(NULL);
    } else {
        perror("Fork Failed");
    }

    

}

int main(){
    char command[4095];

    while(1){
        read_command(command);

        if(strcmp(command, "exit") == 0) {
            printf("symoon shell is terminated...\n");
            break; // "exit" 입력 시, 종료
        }
        else if(strcmp(command, "help") == 0){
            help_command();
        }
        else print_command(command);
    }

    return 0;
}