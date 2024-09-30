#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>  // pid_t를 정의하기 위한 헤더 파일


int main() 
{
    int pipefd[2];
    pid_t pid;
    char buffer[30];

    // 파이프 생성
    if (pipe(pipefd) == -1) 
    {
        perror("Pipe failed");
        exit(1);
    }

    pid = fork();
    
    if (pid < 0) 
    {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) 
    {
        // 자식 프로세스: 파이프에 메시지 쓰기
        close(pipefd[0]);  // 읽기 종료
        char message[] = "Hello from child!";
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]);  // 쓰기 종료
        exit(0);
    } 
    else 
    {
        // 부모 프로세스: 파이프에서 메시지 읽기
        close(pipefd[1]);  // 쓰기 종료
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Received from child: %s\n", buffer);
        close(pipefd[0]);  // 읽기 종료
    }

    return 0;
}
