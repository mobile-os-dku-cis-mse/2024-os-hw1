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
        if (access(fullpath, X_OK) == 0) 
        { 
            return 1; // 실행 파일을 찾음
        }
        path_token = strtok(NULL, ":");
    }

    return 0; // 실행 파일을 찾지 못함
}

// 파이프 처리를 위한 함수
void execute_pipe(char *cmd1, char *cmd2) 
{
    int pipefd[2];
    pipe(pipefd);

    pid_t pid1 = fork();
    if (pid1 == 0) 
    {
        dup2(pipefd[1], STDOUT_FILENO);  // 파이프의 쓰기 끝으로 출력 연결
        close(pipefd[0]);
        close(pipefd[1]);
        char *args1[MAX_ARGS];
        parse_input(cmd1, args1);
        execvp(args1[0], args1);
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) 
    {
        dup2(pipefd[0], STDIN_FILENO);  // 파이프의 읽기 끝으로 입력 연결
        close(pipefd[0]);
        close(pipefd[1]);
        char *args2[MAX_ARGS];
        parse_input(cmd2, args2);
        execvp(args2[0], args2);
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);
}

int main() 
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    char executable_path[MAX_INPUT];
    pid_t pid;
    int status;

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

        // 'cd' 명령어 처리
        if (strncmp(input, "cd", 2) == 0) 
        {
            char *dir = strtok(input + 3, " \n");  // "cd " 이후의 디렉토리 추출
            if (dir == NULL) 
            {
                fprintf(stderr, "No directory specified.\n");
            } 
            else 
            {
                if (chdir(dir) != 0) 
                {
                    perror("chdir failed");
                }
            }
            continue;  // 부모 프로세스에서 처리했으므로 continue
        }

        // 환경 변수 출력 처리 (예: echo $PATH)
        if (input[0] == '$') 
        {
            char *env_var = getenv(input + 1);
            if (env_var) 
            {
                printf("%s\n", env_var);
            } 
            else 
            {
                printf("Environment variable not found.\n");
            }
            continue;
        }

        // 파이프 처리 (| 포함 명령어)
        if (strchr(input, '|') != NULL) 
        {
            char *cmd1 = strtok(input, "|");
            char *cmd2 = strtok(NULL, "|");
            execute_pipe(cmd1, cmd2);
            continue;
        }

        // 명령어와 인자를 분리
        parse_input(input, args);

        // 백그라운드 실행 확인 (& 처리)
        int i = 0;
        while (args[i] != NULL) i++;  // 인자의 끝을 찾음
        int background = 0;

        if (i > 0 && args[i - 1][strlen(args[i - 1]) - 1] == '&') 
        {
            background = 1;  // 백그라운드 실행 플래그 설정
            args[i - 1][strlen(args[i - 1]) - 1] = '\0';  // '&' 제거
        }

        // AND 연산자 처리 (&&)
        if (strstr(input, "&&") != NULL) 
        {
            char *cmd1 = strtok(input, "&&");
            char *cmd2 = strtok(NULL, "&&");

            // 첫 번째 명령어 실행
            pid = fork();
            if (pid == 0) 
            {
                parse_input(cmd1, args);
                if (find_executable(args[0], executable_path)) 
                {
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
            wait(&status);

            // 첫 번째 명령어가 성공한 경우에만 두 번째 명령어 실행
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) 
            {
                pid = fork();
                if (pid == 0) 
                {
                    parse_input(cmd2, args);
                    if (find_executable(args[0], executable_path)) 
                    {
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
                wait(NULL);
            }
            continue;
        }

        // 순차 실행 처리 (; 포함 명령어)
        if (strchr(input, ';') != NULL) 
        {
            char *cmd = strtok(input, ";");
            while (cmd != NULL) 
            {
                pid = fork();
                if (pid == 0) 
                {
                    parse_input(cmd, args);
                    if (find_executable(args[0], executable_path)) 
                    {
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
                wait(NULL);
                cmd = strtok(NULL, ";");
            }
            continue;
        }

        // fork를 통해 자식 프로세스 생성
        pid = fork();

        if (pid == 0) 
        {
            // 자식 프로세스
            if (find_executable(args[0], executable_path)) 
            {
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
            if (!background) 
            {
                wait(NULL);
            }
        } 
        else 
        {
            perror("fork failed");
        }
    }

    return 0;
}
