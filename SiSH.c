#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1600
#define MAX_ARG_SIZE 100
#define MAX_PIPE_SIZE 10

char* find_command_path(const char* command) {
    // 상대 경로와 절대 경로 처리... "./a.out"
    if (access(command, X_OK) == 0) {
        return strdup(command);
    }

    // 환경 변수 받기
    // getenv("PATH")로 얻은 문자열은 읽기 전용 문자열로, 직접 수정할 수 없음
    // 문자열을 복사한 후 수정, 이후 메모리 해제
    char* path = getenv("PATH");
    char* path_copy = strdup(path);
    char* dir = strtok(path_copy, ":");
    static char full_path[MAX_INPUT_SIZE];

    // 여러 환경 변수 경로들에 대해서 access 함수를 통해 실행 가능여부 확인
    while (dir != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            return strdup(full_path);
        }
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

void execute_command(char *input) {
    char *commands[MAX_PIPE_SIZE];
    char *token;
    int num_commands = 0;
    extern char **environ;

    // "ls -al | grep fork"에 대해 파이프 처리
    token = strtok(input, "|");
    while (token != NULL && num_commands < MAX_PIPE_SIZE) {
        commands[num_commands++] = token;
        token = strtok(NULL, "|");
    }
    /*
    commands[0] = ls -al
    commands[1] = grep fork
    */

    int i;
    int fd[2];
    int prev_fd = -1;
    /*
    파이프는 두 프로세스 간의 통신 채널 역할
    fd[0]는 한 프로세스가 데이터를 읽는 쪽(읽기 디스크립터)     ->  "grep <>"이 출력을 읽음
    fd[1]는 다른 프로세스가 데이터를 쓰는 쪽(쓰기 디스크립터)   ->  "ls -al"의 출력이 작성됨
    한 프로세스가 fd[1]을 통해 데이터를 쓸 때, 다른 프로세스는 fd[0]을 통해 그 데이터를 읽어들이는 구조
    두 프로세스 간에 정보 교환 가능
    */

    for (i = 0; i < num_commands; i++) {
        char *args[MAX_ARG_SIZE];
        char *arg_token;
        int j = 0;

        arg_token = strtok(commands[i], " \n");
        while (arg_token != NULL) {
            args[j++] = arg_token;
            arg_token = strtok(NULL, " \n");
        }
        args[j] = NULL;
        /*
        args[0] = ls
        args[1] = -al
        args[2] = NULL
        */

        // 빈 커맨드 처리
        if (j == 0) return;

        // 쉘 종료 처리
        if (strcmp(args[0], "quit") == 0) {
            exit(0);
        }

        // 디렉토리 변경 처리... "cd /home/~"
        if (strcmp(args[0], "cd") == 0) {
            if (j < 2) {
                fprintf(stderr, "cd: missing argument\n");
            } else {
                if (chdir(args[1]) != 0) {
                    perror("cd failed");
                }
            }
            return;
        }

        // 커맨드가 파이프로 이루어진 경우 파이프 생성
        if (i < num_commands - 1) {
            if (pipe(fd) == -1) {
                perror("pipe failed");
                return;
            }
            // printf("----------\n");
            // printf("[%d]New Pipe generated... fd[%d], fd[%d]\n", i, fd[0], fd[1]);
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            return;
        } else if (pid == 0) {
            // Child process
            // printf("[%d]Child Process with %d, %d\n", i, fd[0], fd[1]);
            if (prev_fd != -1) {
                /*
                이전 프로세스에서 생성한 파이프의 읽기 디스크립터인 prev_fd를 현재 프로세스의 표준 입력(STDIN_FILENO)으로 복제
                이전 프로세스가 파이프를 통해 쓴 데이터를 현재 프로세스가 읽을 수 있도록 설정
                */
                // printf("[%d]Child process... prev_fd to STDIN\n", i);
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            if (i < num_commands - 1) {
                /*
                현재 프로세스의 표준 출력(기본적으로 화면에 출력되는 내용)을 fd[1]로 변경
                현재 프로세스가 이 디스크립터를 통해 데이터를 쓸 수 있도록 설정
                */
                // printf("[%d]Child process... fd[1] to STDOUT\n", i);
                
                // 아래 코드에서 STDOUT을 리다이렉션하기에 프린트 문을 여기에 작성
                // printf("[%d]Executing... %s\n", i, commands[i]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }

            // 명령어 PATH 검색
            char* command_path = find_command_path(args[0]);
            if (command_path != NULL) {
                // 지정된 프로그램 실행
                // 현재 프로세스를 완전히 대체, 이후 자동 종료
                execve(command_path, args, environ);
                free(command_path);
                // 여기 코드는 실행되지 않음, 프로세스 대체
            } else {
                fprintf(stderr, "Command not found: %s\n", args[0]);
                exit(1);
            }
        } else {
            // Parent process
            // printf("[%d]Parent Process with %d, %d\n", i, fd[0], fd[1]);
            if (i < num_commands - 1) {
                /*
                파이프가 남아있는 경우
                현재 명령이 파이프의 마지막 명령이 아니라면, 현재 프로세스는 다음 명령에 데이터를 전달해야 함
                다음 명령이 데이터를 읽기 위해 fd[0]를 사용할 것
                현재 프로세스가 쓸 데이터를 모두 보낸 후에는 쓰기 디스크립터인 fd[1]를 닫음

                부모 프로세스는 fd[1]을 사용하지 않기에, if를 통해 체크하지 않고 닫아도 무방
                하지만 논리적으로 파이프가 남아있다면 fd[1]을 사용하지 않는게 이상적
                */
                close(fd[1]);
                // printf("[%d]Parent process... fd[1] closed\n", i);
            }

            if (prev_fd != -1) {
                // printf("[%d]Parent process... prev_fd closed\n", i);
                close(prev_fd);
            }
            // 이전 파이프에서 출력한 결과값 지정
            // printf("[%d]Parent process... prev_fd is defined, waiting\n\n", i);
            prev_fd = fd[0];
            wait(NULL);
        }
    }
}

int main() {
    char input[MAX_INPUT_SIZE];
    char dir[MAX_INPUT_SIZE];

    while (1) {
        // 명령어 받기
        if (getcwd(dir, sizeof(dir)) != NULL) {
            printf("SiSH (%s) >>> ", dir);
        } else {
            perror("getcwd() error");
            continue;
        }
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("Failed to read input");
            continue;
        }

        // 명령어 실행
        execute_command(input);
    }
    return 0;
}

/*
자식 프로세스는 prev_fd값을 통해서 입력을 받을지 말지 선택
자식 프로세스는 파이프 명령어가 있는지 확인 후 출력을 파이프로 전달할지 터미널로 할지 선택
부모 프로세스는 fd[1] 쓰기를 항상 사용하지 않음
부모 프로세스는 자식 프로세스가 뱉은 결과값을 파이프 쌍을 통해 fd[0] 읽기로 지정, 자식 프로세스의 다다음 실행을 위해 전달
*/

/*
구조적으로 부모 프로세스는 다음 동작이 더 이상적
else {
    if (prev_fd != -1) {
        close(prev_fd);
    }
    if (i < num_commands - 1) {
        close(fd[1]);
        prev_fd = fd[0];
    }
    wait(NULL);
}
*/