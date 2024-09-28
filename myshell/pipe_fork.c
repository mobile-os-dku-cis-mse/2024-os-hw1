#include <stdio.h>     // printf, fprintf
#include <stdlib.h>    // malloc, free, exit, getenv, strdup
#include <string.h>    // strtok, strcmp, strlen
#include <unistd.h>    // fork, execve, pid_t, environ
#include <sys/wait.h>  // wait
#include <sys/types.h> // pid_t, struct stat
#include <errno.h>     // perror
#include "other_func.h"  // 헤더 파일 포함


void fork_command_with_pipe(char *command){ // 파이프(|) 존재하는 명령어 처리
    char *cmds[100]; // 명령어 저장 배열
    char *pipe_token = strtok(command, "|");
    int num_pipe = 0;
    // cmds[num_pipe++] = pipe_token;
    while(pipe_token != NULL){
        // printf("cmd: %s\n", pipe_token);
        cmds[num_pipe++] = pipe_token;
        pipe_token = strtok(NULL, "|"); // 다음 명령어
    }
    cmds[num_pipe] = NULL;

    int fd[2 * (num_pipe - 1)]; // pipe 위한 디스크립트 배열

    // 파이프 생성
    for(int i=0;i<num_pipe-1;i++){
        if(pipe(fd + i * 2) == -1){ // 각 프로세스마다 파이프 생성
            perror("pipe");
            exit(1);
        }
    }

    for(int i=0;i<num_pipe;i++){
        pid_t pid = fork();

        if(pid == -1){
            perror("fork");
            exit(1);
        }
        // printf("TESTING: fork pid: %d\n", pid);
        if(pid == 0){
            if(i<num_pipe-1){
                dup2(fd[i*2+1], STDOUT_FILENO);
            }
            if(i > 0){
                dup2(fd[(i-1)*2], STDIN_FILENO);
            }

            for(int j=0;j<2*(num_pipe-1);j++){
                close(fd[j]); // 파이프 닫기
            }
            // 명령어 인자 처리
            char *args[100]; // 인자 배열
            char *token = strtok(cmds[i], " ");
            int k = 0;
            while (token != NULL) {
                args[k++] = token; // 인수 추가
                token = strtok(NULL, " "); // 다음 토큰
            }
            args[k] = NULL; // NULL로 종료

            // PATH 환경 변수 가져오기
            char *path = getenv("PATH");
            if (path == NULL) {
                fprintf(stderr, "PATH environment variable not found\n");
                exit(1);
            }

            char *copyPath = strdup(path); // 문자열 복제
            // printf("cmd: %s\n", copyPath);
            execve_command(copyPath, args, k);
            
            free(copyPath); // strdup한 메모리 해제는 이곳에서 처리
        }
    }

    // 부모 프로세스: 모든 파이프 닫기
    for (int i = 0; i < 2 * (num_pipe - 1); i++) {
        close(fd[i]);
    }

    // 모든 자식 프로세스가 종료될 때까지 기다리기
    for (int i = 0; i < num_pipe; i++) {
        wait(NULL);
    }
}