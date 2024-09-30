#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define NUM_CHILDREN 5


int main() 
{
    pid_t child_pids[NUM_CHILDREN];
    int i;

    // 여러 자식 프로세스 생성
    for (i = 0; i < NUM_CHILDREN; i++) 
    {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } 
        else if (pid == 0) 
        {
            // 자식 프로세스
            printf("Child %d with PID %d reporting for duty!\n", i + 1, getpid());
            exit(0);
        } 
        else 
        {
            // 부모 프로세스
            child_pids[i] = pid;
        }
    }

    // 모든 자식 프로세스 종료 대기
    for (i = 0; i < NUM_CHILDREN; i++) 
    {
        int status;
        waitpid(child_pids[i], &status, 0);
        printf("Child with PID %d has finished.\n", child_pids[i]);
    }

    printf("All children have reported and finished.\n");

    return 0;
}
