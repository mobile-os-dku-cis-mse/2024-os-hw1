#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_COMMAND 1024 // 최대 명령어 길이
#define MAX_ARGS 128     // 최대 명령어 arguments / 토큰 개수
#define MAX_PATH 1024

// prompt 띄우는 함수
void prompt(char *input)
{
    char host_name[MAX_ARGS], current_path[MAX_ARGS];

    gethostname(host_name, MAX_ARGS); // 현재 호스트 이름 가져오기
    getcwd(current_path, MAX_ARGS);   // 현재 디렉토리 가져오기

    printf("SiSh@%s( %s ) : ", host_name, current_path); // Prompt에 띄워지는 문자 띄우기
    if (fgets(input, MAX_ARGS, stdin) == NULL)
    {
        return;
    }

    if (input[strlen(input) - 1] == '\n')
    {
        input[strlen(input) - 1] = '\0'; // 개행 문자 제거
    }
}

// input을 여러 token으로 쪼갠 후 args 에 각각 쪼개주는 함수
void parse_input(char *input, char **args)
{
    int i = 0;
    int in_quotes = 0;
    char *start = input;
    char *current = input;

    while (*current != '\0')
    {
        // 공백을 무시하고 다음 토큰으로 이동
        if (*current == ' ' && !in_quotes)
        {
            *current = '\0';
            if (*start != '\0')
            {
                args[i++] = start; // 토큰 저장
            }
            start = current + 1; // 다음 토큰 시작 위치로 이동
        }
        else if (*current == '"') // 따옴표 처리
        {
            if (in_quotes)
            {
                *current = '\0'; // 따옴표를 null로 변환
                args[i++] = start; // 따옴표 안의 문자열 저장
                in_quotes = 0; // 따옴표 끝
                start = current + 1;
            }
            else
            {
                in_quotes = 1; // 따옴표 시작
                start = current + 1; // 따옴표 다음에서 시작
            }
        }
        current++;
    }

    if (*start != '\0') // 마지막 토큰 처리
    {
        args[i++] = start;
    }

    args[i] = NULL; // 인자 끝에 null 추가

}

// 파이프 및 리다이렉션을 처리하는 함수
void handle_redirection_and_pipe(char **args)
{
    int fd;
    int pipefd[2];
    int has_input_redir = 0, has_output_redir = 0, has_pipe = 0;
    int input_index = -1, output_index = -1, pipe_index = -1;

    // 파이프가 존재하는지 확인
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "<") == 0) {
            has_input_redir = 1;
            input_index = i;
        } else if (strcmp(args[i], ">") == 0) {
            has_output_redir = 1;
            output_index = i;
        } else if (strcmp(args[i], "|") == 0) {
            has_pipe = 1;
            pipe_index = i;
        }
    }

    // 입력 리다이렉션 처리
    if (has_input_redir) {
        fd = open(args[input_index + 1], O_RDONLY);
        if (fd == -1) {
            perror("open input file failed");
            return;
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
        args[input_index] = NULL; // 리다이렉션 기호 제거
    }

    // 출력 리다이렉션 처리
    if (has_output_redir) {
        fd = open(args[output_index + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("open output file failed");
            return;
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        args[output_index] = NULL; // 리다이렉션 기호 제거
    }

    // 파이프 처리
    if (has_pipe) {
        args[pipe_index] = NULL; // 파이프 앞 명령어와 뒤 명령어를 분리

        pipe(pipefd);
        pid_t pid = fork();

        if (pid == 0) { // 자식 프로세스: 첫 번째 명령어 실행
            dup2(pipefd[1], STDOUT_FILENO); // 파이프의 쓰기 끝을 표준 출력에 연결
            close(pipefd[0]); // 읽기 끝 닫기
            close(pipefd[1]);
            execvp(args[0], args); // 첫 번째 명령어 실행 (예: "ls -l")
            perror("execvp failed");
            exit(1);
        } else { // 부모 프로세스: 두 번째 명령어 실행
            wait(NULL);
            dup2(pipefd[0], STDIN_FILENO); // 파이프의 읽기 끝을 표준 입력에 연결
            close(pipefd[1]); // 쓰기 끝 닫기
            close(pipefd[0]);
            execvp(args[pipe_index + 1], &args[pipe_index + 1]); // 두 번째 명령어 실행 (예: "grep .c")
            perror("execvp failed");
            exit(1);
        }
    }

    // 파이프가 없을 경우 명령어 실행
    execvp(args[0], args);
    perror("execvp failed");
}



// 현재 작업 디렉토리를 출력하는 함수
void print_current_directory()
{
    char cwd[MAX_PATH];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("Current working directory: %s\n", cwd);
    }
    else
    {
        perror("getcwd failed");
    }
}

// 작업 디렉토리를 변경하는 함수
void change_directory(const char *path)
{
    if (chdir(path) == 0)
    {
        char cwd[MAX_PATH];
        getcwd(cwd, sizeof(cwd));
        printf("Directory changed to: %s\n", cwd);
    }
    else
    {
        perror("chdir failed");
    }
}

// 모든 환경 변수를 출력하는 함수
void list_environment_variables()
{
    extern char **environ;
    for (int i = 0; environ[i] != NULL; i++)
    {
        printf("%s\n", environ[i]);
    }
}

// 환경 변수를 설정하는 함수
void set_environment_variable(const char *var, const char *value)
{
    if (setenv(var, value, 1) == 0)
    {
        printf("Environment variable %s set to %s\n", var, value);
    }
    else
    {
        perror("setenv failed");
    }
}

int main(int argc, char *argv[])
{
    char input[MAX_COMMAND]; // user input
    char *args[MAX_ARGS];
    int child_status;
    pid_t pid;

    while (1)
    {
        printf("\n");
        prompt(input);

        if (strcmp(input, "quit") == 0)
        {
            printf("Quit SiSH\n");
            break;
        }

        parse_input(input, args);

        if (args[0] == NULL || strlen(args[0]) == 0)
        {
            continue;
        }

        if (strcmp(args[0], "cd") == 0)
        {
            if (args[1] == NULL)
            {
                fprintf(stderr, "Expected argument to \"cd\"\n");
            }
            else
            {
                change_directory(args[1]);
            }
            continue;
        }

        pid = fork();
        if (pid < 0)
        {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0)
        {
            // explore, fedit, devproc 명령어 처리
            if ((strcmp(args[0], "explore") == 0) || (strcmp(args[0], "fedit") == 0) || (strcmp(args[0], "devproc") == 0))
            {
                char *args_execve[MAX_ARGS];
                int i;

                args_execve[0] = malloc(strlen(args[0]) + 3); // "./"와 널 문자를 위해 3바이트 추가
                if (args_execve[0] == NULL)
                {
                    perror("malloc failed");
                    exit(1);
                }

                strcpy(args_execve[0], "./");
                strcat(args_execve[0], args[0]);

                for (i = 1; args[i] != NULL; i++)
                {
                    args_execve[i] = malloc(strlen(args[i - 1]) + 1);
                    strcpy(args_execve[i], args[i]);
                }

                args_execve[i] = NULL;
                execv(args_execve[0], args_execve);

                for (int j = 0; j <= i; j++)
                {
                    free(args_execve[j]);
                }

                perror("execv failed");
                exit(1);
            }
            else
            {
                // 파이프 또는 리다이렉션 처리
                handle_redirection_and_pipe(args);
            }
        }
        else
        {
            wait(&child_status);
        }
    }

    return 0;
}
