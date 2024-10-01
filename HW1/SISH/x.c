#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 100
#define MAX_PIPES 10
#define MAX_JOBS 20
#define MAX_HISTORY 1000

// 잡 구조체
typedef struct {
    pid_t pid;
    char command[BUFFER_SIZE];
    int is_background;
} Job;

Job jobs[MAX_JOBS];
int job_count = 0;
char *command_history[MAX_HISTORY];
int history_count = 0;

void execute_command(char *command);
void handle_getenv_command(char *args[], int arg_count);
char* find_command_in_path(char *command);
void display_prompt();
void parse_command(char *command, char *args[], int *arg_count);
void execute_pipeline(char *commands[], int num_commands);
void handle_redirection(char *args[], int *arg_count);
void add_job(pid_t pid, char *command, int is_background);
void list_jobs();
void bring_to_foreground(int job_id);
void send_to_background(int job_id);
void handle_sigchld(int sig);
char* command_generator(const char* text, int state);
char** command_completion(const char* text, int start, int end);
void initialize_readline();
void add_to_history(const char* command);

int main() {
    char *buffer;
    
    signal(SIGCHLD, handle_sigchld);

    initialize_readline();

    while (1) {
        //display_prompt();
        //buffer = readline("");
        buffer = readline("SiSH >>> ");

        if (buffer == NULL) {
            printf("\n");
            break;
        }

        if (strcmp(buffer, "quit") == 0) {
            break;
        }

        if (strlen(buffer) > 0) {
            add_history(buffer);
            add_to_history(buffer);
            execute_command(buffer);
        }



        free(buffer);
    }

    clear_history();
    for (int i = 0; i < history_count; i++) {
        free(command_history[i]);
    }

    return 0;
}


void execute_command(char *command) {
    char *commands[MAX_PIPES];
    int num_commands = 0;
    char *token = strtok(command, "|");
    int is_background = 0;

    
    while (token != NULL && num_commands < MAX_PIPES) {
        commands[num_commands++] = token;
        token = strtok(NULL, "|");
    }

    if (num_commands > 0) {
        char *last_command = commands[num_commands - 1];
        int len = strlen(last_command);
        if (len > 0 && last_command[len - 1] == '&') {
            is_background = 1;
            last_command[len - 1] = '\0';  
        }
    }

    if (num_commands > 1) {
        execute_pipeline(commands, num_commands);
    } else {
        char *args[MAX_ARGS];
        int arg_count = 0;
        parse_command(commands[0], args, &arg_count);

        if (arg_count == 0) return;

        if (strcmp(args[0], "getenv") == 0) {
            handle_getenv_command(args, arg_count);
            return;
        }

        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL || chdir(args[1]) != 0) {
                perror("cd failed");
            }
            return;
        }

        if (strcmp(args[0], "jobs") == 0) {
            list_jobs();
            return;
        }

        if (strcmp(args[0], "fg") == 0) {
            if (args[1] != NULL) {
                bring_to_foreground(atoi(args[1]));
            }
            return;
        }

        if (strcmp(args[0], "bg") == 0) {
            if (args[1] != NULL) {
                send_to_background(atoi(args[1]));
            }
            return;
        }

        if (strcmp(args[0], "history") == 0) {
            for (int i = 0; i < history_count; i++) {
                printf("%d: %s\n", i + 1, command_history[i]);
            }
            return;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
        } else if (pid == 0) {
            // Child process
            handle_redirection(args, &arg_count);

            char *path = find_command_in_path(args[0]);
            if (path != NULL) {
                execve(path, args, NULL);
                perror("execve failed");
                free(path);
            } else if (args[0][0] == '.' && args[0][1] == '/') {
                // Execute file in current directory
                execve(args[0], args, NULL);
                perror("execve failed");
            } else {
                fprintf(stderr, "Command not found: %s\n", args[0]);
            }
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            if (!is_background) {
                int status;
                waitpid(pid, &status, 0);
            } else {
                add_job(pid, command, 1);
                printf("[%d] %d\n", job_count, pid);
            }
        }
    }
}

void handle_redirection(char *args[], int *arg_count) {
    for (int i = 0; i < *arg_count; i++) {
        if (strcmp(args[i], ">") == 0 || strcmp(args[i], ">>") == 0) {
            if (i + 1 < *arg_count) {
                int flags = O_WRONLY | O_CREAT;
                if (strcmp(args[i], ">>") == 0) {
                    flags |= O_APPEND;
                } else {
                    flags |= O_TRUNC;
                }
                int fd = open(args[i + 1], flags, 0644);
                if (fd == -1) {
                    perror("open failed");
                    return;
                }
                dup2(fd, STDOUT_FILENO);
                close(fd);
                args[i] = NULL;
                *arg_count = i;
            }
            break;
        } else if (strcmp(args[i], "<") == 0) {
            if (i + 1 < *arg_count) {
                int fd = open(args[i + 1], O_RDONLY);
                if (fd == -1) {
                    perror("open failed");
                    return;
                }
                dup2(fd, STDIN_FILENO);
                close(fd);
                args[i] = NULL;
                *arg_count = i;
            }
            break;
        } else if (strcmp(args[i], "2>") == 0) {
            if (i + 1 < *arg_count) {
                int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1) {
                    perror("open failed");
                    return;
                }
                dup2(fd, STDERR_FILENO);
                close(fd);
                args[i] = NULL;
                *arg_count = i;
            }
            break;
        } else if (strcmp(args[i], "2>&1") == 0) {
            dup2(STDOUT_FILENO, STDERR_FILENO);
            args[i] = NULL;
            *arg_count = i;
            break;
        }
    }
}

void add_job(pid_t pid, char *command, int is_background) {
    if (job_count < MAX_JOBS) {
        jobs[job_count].pid = pid;
        strncpy(jobs[job_count].command, command, BUFFER_SIZE);
        jobs[job_count].is_background = is_background;
        job_count++;
    } else {
        fprintf(stderr, "Maximum number of jobs reached\n");
    }
}

void list_jobs() {
    for (int i = 0; i < job_count; i++) {
        printf("[%d] %d %s %s\n", i + 1, jobs[i].pid, 
               jobs[i].is_background ? "Running" : "Stopped", 
               jobs[i].command);
    }
}

void bring_to_foreground(int job_id) {
    if (job_id > 0 && job_id <= job_count) {
        int status;
        pid_t pid = jobs[job_id - 1].pid;
        
        if (kill(pid, SIGCONT) < 0) {
            perror("kill (SIGCONT)");
        }
        
        waitpid(pid, &status, WUNTRACED);
        
        if (WIFSTOPPED(status)) {
            printf("Job [%d] stopped\n", job_id);
            jobs[job_id - 1].is_background = 0;
        } else {
            // Remove the job from the list
            for (int i = job_id - 1; i < job_count - 1; i++) {
                jobs[i] = jobs[i + 1];
            }
            job_count--;
        }
    } else {
        fprintf(stderr, "Invalid job ID\n");
    }
}

void send_to_background(int job_id) {
    if (job_id > 0 && job_id <= job_count) {
        pid_t pid = jobs[job_id - 1].pid;
        
        if (kill(pid, SIGCONT) < 0) {
            perror("kill (SIGCONT)");
        } else {
            jobs[job_id - 1].is_background = 1;
            printf("[%d] %d continued\n", job_id, pid);
        }
    } else {
        fprintf(stderr, "Invalid job ID\n");
    }
}

void handle_sigchld(int sig) {
    pid_t pid;
    int status;
    
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        for (int i = 0; i < job_count; i++) {
            if (jobs[i].pid == pid) {
                if (WIFEXITED(status) || WIFSIGNALED(status)) {
                    printf("[%d] Done %s\n", i + 1, jobs[i].command);
                    // Remove the job from the list
                    for (int j = i; j < job_count - 1; j++) {
                        jobs[j] = jobs[j + 1];
                    }
                    job_count--;
                }
                break;
            }
        }
    }
}

void display_prompt() {
    char cwd[BUFFER_SIZE];
    char *user = getenv("USER");
    char *pwd = getcwd(cwd, sizeof(cwd));
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char time_buf[9];

    strftime(time_buf, 9, "%H:%M:%S", tm_info);

    if (user != NULL && pwd != NULL) {
        printf("%s : %s [%s] : SiSH >>> ", user, pwd, time_buf);
    } else {
        printf("SiSH >>> ");
    }

    fflush(stdout);
}


void parse_command(char *command, char *args[], int *arg_count) {
    char *token = strtok(command, " \t");
    *arg_count = 0;
    while (token != NULL && *arg_count < MAX_ARGS - 1) {
        args[(*arg_count)++] = token;
        token = strtok(NULL, " \t");
    }
    args[*arg_count] = NULL;
}

void execute_pipeline(char *commands[], int num_commands) {
    int pipes[MAX_PIPES - 1][2];
    pid_t pids[MAX_PIPES];

    for (int i = 0; i < num_commands - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe failed");
            return;
        }
    }

    for (int i = 0; i < num_commands; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork failed");
            return;
        } else if (pids[i] == 0) {
            // Child process
            if (i > 0) {
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }
            if (i < num_commands - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }

            for (int j = 0; j < num_commands - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            char *args[MAX_ARGS];
            int arg_count = 0;
            parse_command(commands[i], args, &arg_count);
            handle_redirection(args, &arg_count);

            char *path = find_command_in_path(args[0]);
            if (path != NULL) {
                execve(path, args, NULL);
                perror("execve failed");
                free(path);
            } else {
                fprintf(stderr, "Command not found: %s\n", args[0]);
            }
            exit(EXIT_FAILURE);
        }
    }

    // Parent process
    for (int i = 0; i < num_commands - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (int i = 0; i < num_commands; i++) {
        waitpid(pids[i], NULL, 0);
    }
}


// getenv 명령어 처리 함수
void handle_getenv_command(char *args[], int arg_count) {
    int i, j;
    char *env, *str;
    char *tok[100], *saveptr;

    // 인자가 없는 경우 사용법 출력
    if (arg_count == 1) {
        printf("usage: getenv env_vars ... \n");
        return;
    }

    // 각 환경 변수를 처리한다
    for (i = 1; i < arg_count; i++) {
        env = getenv(args[i]);  // 환경 변수를 가져온다
        if (env == NULL) {
            printf("%s is not set\n", args[i]);
            continue;
        }

        printf("%s=%s\n", args[i], env);  // 환경 변수를 출력한다

        // 경로들을 출력한다 ( ':' 으로 구분이됨 )
        for (j = 0, str = env; ; str = NULL, j++) {
            tok[j] = strtok_r(str, ":", &saveptr);  // ':'로 구분된 토큰 처리한다
            if (tok[j] == NULL) break;
            printf("\t%s\n", tok[j]);  // 각 경로를 출력한다.
        }

        printf("***---------------------***\n");
    }
}

// PATH에서 명령어의 절대 경로를 찾는 함수
char* find_command_in_path(char *command) {
    char *path_env = getenv("PATH");
    if (path_env == NULL) {
        return NULL;  // PATH 환경 변수가 없으면 명령어를 찾을 수 없음
    }

    char *path = strdup(path_env);  // PATH 문자열 복사
    char *dir = strtok(path, ":");  // ':'로 구분된 각 디렉토리 처리
    struct stat sb;
    char full_path[BUFFER_SIZE];

    while (dir != NULL) {
        // 디렉토리와 명령어 이름을 결합하여 전체 경로 생성
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

        // 해당 경로에 실행 파일이 있는지 확인
        if (stat(full_path, &sb) == 0 && sb.st_mode & S_IXUSR) {
            free(path);  // 메모리 해제
            return strdup(full_path);  // 명령어 절대 경로 반환
        }

        dir = strtok(NULL, ":");  // 다음 디렉토리로 이동
    }

    free(path);  // 메모리 해제
    return NULL;  // 명령어를 찾지 못함
}

char* command_generator(const char* text, int state) {
    static int len;
    static DIR *dir;
    static struct dirent *ent;
    char *name;

    if (!state) {
        len = strlen(text);
        if (dir) closedir(dir);
        dir = opendir(".");
    }

    while ((ent = readdir(dir)) != NULL) {
        name = ent->d_name;
        if (strncmp(name, text, len) == 0) {
            char *r = malloc(strlen(name) + 1);
            strcpy(r, name);
            return r;
        }
    }

    return NULL;
}

char** command_completion(const char* text, int start, int end) {
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, command_generator);
}

void initialize_readline() {
    rl_attempted_completion_function = command_completion;
}

void add_to_history(const char* command) {
    if (history_count < MAX_HISTORY) {
        command_history[history_count] = strdup(command);
        history_count++;
    } else {
        free(command_history[0]);
        for (int i = 1; i < MAX_HISTORY; i++) {
            command_history[i-1] = command_history[i];
        }
        command_history[MAX_HISTORY-1] = strdup(command);
    }
}