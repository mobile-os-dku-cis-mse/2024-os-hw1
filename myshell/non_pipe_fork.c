#include <stdio.h>     // printf, fprintf
#include <stdlib.h>    // malloc, free, exit, getenv, strdup
#include <string.h>    // strtok, strcmp, strlen
#include <unistd.h>    // fork, execve, pid_t, environ
#include <sys/wait.h>  // wait
#include <sys/types.h> // pid_t, struct stat
#include <sys/stat.h>  // stat
#include <errno.h>     // perror
#include "other_func.h"  // 헤더 파일 포함

extern char **environ;

void execve_command(char *copyCommand, char **args, int i) {
    // "env" 명령어 처리
    if (strcmp(args[0], "env") == 0) {
        echo_getenv(i, args);
        exit(0); // env 명령어 처리 후 종료
    }

    // gcc와 cc1의 경로 설정
    char *new_path = malloc(strlen(copyCommand) + 3); // gcc_path의 길이도 포함
    sprintf(new_path, ".:%s", copyCommand); // gcc_path를 포함한 새로운 경로 생성
    char *dirToken = strtok(new_path, ":"); // 첫 번째 디렉토리 경로
    char *fullPath = NULL;

    while (dirToken != NULL) {
        fullPath = malloc(strlen(dirToken) + strlen(args[0]) + 2); // 경로 + 명령어 + '/'
        sprintf(fullPath, "%s/%s", dirToken, args[0]);
        
        struct stat buffer;
        if (stat(fullPath, &buffer) == 0) { // 파일이 존재하는지 확인
            if (execve(fullPath, args, environ) == -1) { // env를 NULL로 설정
                perror("execve failed");
            }
            free(fullPath);
            free(new_path);
            exit(1); // execve가 성공하면 여기로 오지 않음
        }
        
        free(fullPath);
        dirToken = strtok(NULL, ":"); // 다음 경로로 이동
    }

    fprintf(stderr, "%s: Command not found\nIf you are curious about other commands, check out 'help'.\n", args[0]);
    free(new_path);
    exit(1);
}


void fork_command(char *command) {
    pid_t pid = fork();
    if (pid == 0) { // 자식 프로세스
        char *args[100]; // 인자 배열
        char *token = strtok(command, " ");
        int i = 0;
        while (token != NULL) {
            args[i++] = token; // 인수 추가
            token = strtok(NULL, " "); // 다음 토큰
        }
        args[i] = NULL; // NULL로 종료

        // PATH 환경 변수 가져오기
        char *path = getenv("PATH");
        if (path == NULL) {
            fprintf(stderr, "PATH environment variable not found\n");
            exit(1);
        }

        char *copyCommand = strdup(path); // 문자열 복제
        execve_command(copyCommand, args, i);
        
        free(copyCommand); // strdup한 메모리 해제는 이곳에서 처리
    } else if (pid > 0) {
        wait(NULL); // 부모 프로세스는 자식 프로세스를 기다림
    } else {
        perror("Fork Failed");
    }
}
