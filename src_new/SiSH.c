//
// Created by hochacha on 24. 9. 28.
//

#include "SiSH.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <bits/posix2_lim.h>
#include <sys/wait.h>

#include "instruction_parser.h"
#include "../src/argument_parser.h"
#define INPUT_MAX 1024
#define CWD_MAX 1024

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
    printf("%s@%s $", host.host, host.hostname);
    getcwd(cwd, CWD_MAX);
    printf("%s", cwd);
}


int run_shell() {
    init_shell();

    while(terminate == 1) {

        // CLI Format jobs
        show_basic_prompt_everyline();
        fflush(stdout);

        // get input
        fgets(input, INPUT_MAX, stdin);

        // strip out NL character
        if((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
            input[strlen(input) - 1] = '\0';

        if(strcmp(input, "exit") == 0){
            terminate = 0;
            continue;
        }

        // initialize parser
        // the parser just valid during a single input, not a single instruction which is composed with pipe
        // and redirection
        parser_state *state = init_parser(input);
        parsed_instruction *parsed_instruction = NULL;

        int pipefd[2];
        int prev_fd = -1;

        while((parsed_instruction = parse_next_instruction(state)) != NULL) {
            char* args[INPUT_MAX / 2 + 1] = {0,};
            // parse argument from a single instruction
            argument_parser(parsed_instruction->instruction, args);

            args[0] = bin_path_finder(args[0]);
            file_path_finder(args);

            pid_t pid = fork();
            if(pid < 0) {
                fprintf(stderr, "fork failed\n");
                return 1;
            }
            else if(pid == 0) {
                if(execv(args[0], args) == -1) {
                    perror("execv failed - ");
                    exit(EXIT_FAILURE);
                }
            }
            else {
                wait(NULL);
            }
            free_parsed_instruction(parsed_instruction);
        }
        free_parser(state);
    }
    return 0;
}