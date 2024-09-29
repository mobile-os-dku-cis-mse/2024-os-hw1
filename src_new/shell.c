//
// Created by hochacha on 24. 9. 28.
//

#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "instruction_parser.h"
#include "argument_parser.h"
#include "tools/builtin_commands.h"
#include "tools/path_finder.h"

#define INPUT_MAX 1024
#define CWD_MAX 1024
#define ARG_MAX (INPUT_MAX / 2 + 1)

#define BUILTIN_NONE 0
#define BUILTIN_PARENT 1
#define BUILTIN_CHILD 2

shell_runner host;
char input[INPUT_MAX];
char cwd[CWD_MAX];
int terminate;

void init_shell() {
    gethostname(host.hostname, sizeof(host.hostname));
    host.host = getlogin();
    host.uid = getuid();
}

void show_basic_prompt_everyline() {
    printf("%s@%s~$", host.host, host.hostname);
    getcwd(cwd, CWD_MAX);
    printf("%s ", cwd);
}

int builtin_command_checker(char* arg) {
    if (strcmp(arg, "cd") == 0) {
        return BUILTIN_PARENT;
    }
    if (strcmp(arg, "echo") == 0 || strcmp(arg, "pwd") == 0) {
        return BUILTIN_CHILD;
    }
    return BUILTIN_NONE;
}

int builtin_runner(int argc, char* arg[ARG_MAX]) {
    if (strcmp(arg[0], "cd") == 0) {
        return change_directory(arg);
    }
    if (strcmp(arg[0], "echo") == 0) {
        return echo(arg);
    }
    if (strcmp(arg[0], "pwd") == 0) {
        printf("%s\n", getcwd(cwd, CWD_MAX));
        return 0;
    }
    return 0;
}

int run_shell() {
    init_shell();

    while(terminate != 1) {

        // CLI Format jobs
        show_basic_prompt_everyline();
        fflush(stdout);

        // get input
        fgets(input, INPUT_MAX, stdin);

        // strip out NL character
        if((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
            input[strlen(input) - 1] = '\0';

        if(strcmp(input, "exit") == 0){
            terminate = 1;
            continue;
        }

        // initialize parser
        // the parser just valid during a single input, not a single instruction which is composed with pipe
        // and redirection
        parser_state *state = init_parser(input);
        parsed_instruction *parsed_instruction = NULL;

        int in_fd = 0;
        int out_fd = 1;
        int fd[2];
        pid_t pid;

        while((parsed_instruction = parse_next_instruction(state)) != NULL) {
            char* args[ARG_MAX] = {0,};
            // parse argument from a single instruction
            const int args_num = argument_parser(parsed_instruction->instruction, args);

            int builtin_type = builtin_command_checker(args[0]);
            if (builtin_type == BUILTIN_PARENT) {
                // 부모 프로세스에서 실행해야 하는 명령어 처리
                builtin_runner(args_num, args);
                continue;
            }

            args[0] = bin_path_finder(args[0]);
            file_path_prefixer(args, args_num);

            // creating pipe
            if (parsed_instruction->delimiter == '|') {
                if (pipe(fd) == -1) {
                    perror("fail to pipe");
                    exit(EXIT_FAILURE);
                }
                out_fd = fd[1];
            } else if (parsed_instruction->delimiter == '>') {
                // 리다이렉션 처리
                parsed_instruction = parse_next_instruction(state);
                if (parsed_instruction == NULL) {
                    fprintf(stderr, "redicted file is not designated\n");
                    exit(EXIT_FAILURE);
                }
                out_fd = open(parsed_instruction->instruction, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (out_fd == -1) {
                    perror("fail to open file");
                    exit(EXIT_FAILURE);
                }
            } else {
                out_fd = 1;
            }

            pid_t pid = fork();
            if (pid == -1) {
                perror("fail to fork - ");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // 자식 프로세스

                if (in_fd != 0) {
                    dup2(in_fd, STDIN_FILENO);
                    close(in_fd);
                }
                if (out_fd != 1) {
                    dup2(out_fd, STDOUT_FILENO);
                    if (parsed_instruction->delimiter == '|') {
                        close(fd[0]);
                        close(fd[1]);
                    }
                }

                if (builtin_type == BUILTIN_CHILD) {
                   // child builtin
                    builtin_runner(args_num, args);
                    exit(0);
                } else {
                    //args[0] = bin_path_finder(args[0]);
                    //file_path_prefixer(args, args_num);
                    if (execv(args[0], args) == -1) {
                        perror("fail to execv - ");
                        exit(EXIT_FAILURE);
                    }
                }
            } else {
                // 부모 프로세스
                wait(NULL);
                if (in_fd != 0)
                    close(in_fd);
                if (out_fd != 1)
                    close(out_fd);
                if (parsed_instruction->delimiter == '|') {
                    in_fd = fd[0];
                } else {
                    in_fd = 0;
                }
            }
            out_fd = 1;
        }
        free_parser(state);
    }
    return 0;
}