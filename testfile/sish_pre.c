#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

// 명령어 입력을 분리하는 함수
void parse_input(char *input, char **args) 
{
    char *token;
    int i = 0;

    // strtok을 이용하여 공백으로 분리
    token = strtok(input, " \n");

    while (token != NULL) 
    {
        args[i] = token;
        i++;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL; // 마지막에 NULL을 추가하여 execve에 전달할 수 있게 함
}

// PATH 환경 변수를 사용해 실행 파일의 전체 경로를 찾는 함수
int find_executable(char *command, char *fullpath) 
{
    char *path = getenv("PATH");
    char *path_token;
    char path_copy[MAX_INPUT];

    strcpy(path_copy, path); // PATH 복사
    path_token = strtok(path_copy, ":");

    // 각 디렉토리를 순차적으로 검사하여 실행 파일을 찾음
    while (path_token != NULL) 
    {
        snprintf(fullpath, MAX_INPUT, "%s/%s", path_token, command);
        if (access(fullpath, X_OK) == 0) // 실행 가능한 파일인지 확인
        { 
            return 1; // 실행 파일을 찾음
        }
        path_token = strtok(NULL, ":");
    }

    return 0; // 실행 파일을 찾지 못함
}

int main() 
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    char executable_path[MAX_INPUT];
    pid_t pid;

    while (1) 
    {
        // 프롬프트 출력
        printf("SiSH> ");
        fgets(input, MAX_INPUT, stdin);

        // 'quit' 입력 시 종료
        if (strncmp(input, "quit", 4) == 0) 
        {
            break;
        }

        // 명령어와 인자를 분리
        parse_input(input, args);

        // fork를 통해 자식 프로세스 생성
        pid = fork();

        if (pid == 0) 
        {
            // 자식 프로세스
            if (find_executable(args[0], executable_path)) 
            {
                // 프로그램 실행
                execve(executable_path, args, NULL);
                perror("execve failed");
                exit(EXIT_FAILURE);
            } 
            else 
            {
                printf("Command not found: %s\n", args[0]);
                exit(EXIT_FAILURE);
            }
        } 
        
        else if (pid > 0) 
        {
            // 부모 프로세스: 자식 프로세스가 끝날 때까지 대기
            wait(NULL);
        } 
        else 
        {
            perror("fork failed");
        }
    }

    return 0;
}


// 'echo' 명령어와 환경 변수 처리
/*
if (strcmp(args[0], "echo") == 0) 
{
    for (int i = 1; args[i] != NULL; i++) 
    {
        if (args[i][0] == '$') 
        {
            char *env_var = getenv(args[i] + 1);
            if (env_var) 
            {
                printf("%s ", env_var);
            } 
            else 
            {
                printf("Environment variable not found ");
            }
        } else 
        {
            printf("%s ", args[i]);
        }
    }
    printf("\n");
    continue;
}
*/