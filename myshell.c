#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void read_command(char *command) {
    printf("myshell> ");
    fgets(command, 1024, stdin);
    command[strcspn(command, "\n")] = 0; // 줄 바꿈 제거
}

void execute_command(char *command) {
    pid_t pid = fork();
    if (pid == 0) { // 자식 프로세스
        char *argv[100];
        char *token = strtok(command, " ");
        int i = 0;
        while (token != NULL) {
            argv[i++] = token;
            token = strtok(NULL, " ");
        }
        argv[i] = NULL; // 마지막 인자는 NULL로 설정
        execvp(argv[0], argv); // 명령어 실행
        perror("execvp failed"); // 실행 실패 시 오류 출력
        exit(1);
    } else if (pid > 0) { // 부모 프로세스
        wait(NULL); // 자식 프로세스가 종료될 때까지 대기
    } else {
        perror("fork failed"); // fork 실패 시 오류 출력
    }
}

int main() {
    char command[1024];
    while (1) {
        read_command(command);
        if (strcmp(command, "exit") == 0) {
            break; // 'exit' 입력 시 종료
        }
        execute_command(command);
    }
    return 0;
}
