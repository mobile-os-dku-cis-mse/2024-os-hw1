#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024 // 입력 버퍼 크기

// 명령어 입력 받기
void read_command(char *buffer) {
    printf("my_shell> ");
    fgets(buffer, MAX_LINE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // 개행 문자 제거
}

// 명령어 실행하기
void execute_command(char *command) {
    char *args[MAX_LINE / 2 + 1]; // 명령어 인수 배열
    int i = 0;

    // 명령어를 공백 기준으로 분리
    args[i] = strtok(command, " ");
    while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, " ");
    }

    // 자식 프로세스에서 명령어 실행
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // 자식 프로세스: execvp로 명령 실행
        if (execvp(args[0], args) == -1) {
            perror("execvp failed");
        }
        exit(1);
    } else {
        // 부모 프로세스: 자식 프로세스가 끝날 때까지 대기
        wait(NULL);
    }
}

int main() {
    char command[MAX_LINE];

    // 기본 셸 루프
    while (1) {
        // 명령어 입력 받기
        read_command(command);

        // "exit" 입력 시 종료
        if (strcmp(command, "exit") == 0) {
            break;
        }

        // 명령어 실행
        execute_command(command);
    }

    return 0;
}

