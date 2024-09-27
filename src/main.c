#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 
#include <sys/wait.h>
#include <sys/stat.h> 
#include <errno.h>
#include <limits.h>
#include "instruction_parser.h"

int pids[10];
int count;
int flag = 0;

#define MAX_LINE 80

int main() {
    char * args[MAX_LINE / 2 + 1];
    char input[MAX_LINE];
    int should_run = 1;
    char cwd[PATH_MAX];

    // running SiSH Script
    while (should_run){

        // ready to get the input
        // TODO: current working directory를 출력하도록 변경
        printf("SiSH> ");
        fflush(stdout);

        fgets(input, MAX_LINE, stdin);
        
        // strip out NL character
        if((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
            input[strlen(input) - 1] = '\0';

        // check the exit command - is it exit?
        // terminate condition
        if(strcmp(input, "exit") == 0){
            should_run = 0;
            continue;
        }
        
        // checking wild card character
        /* skipped */
        
        // parsing the input
        // TODO: make it as a function named "parser"

        ParserState *state = init_parser(input);

        ParsedInstruction *parse_inst; 
        while((parse_inst = parse_next_instruction(state)) != NULL){
#ifdef DEBUG
            printf("Instruction: %s\n", parse_inst->instruction);
            printf("Delimiter: %c\n", parse_inst->delimiter);
#endif
            pid_t pid = fork();

            if(pid < 0){
                fprintf(stderr, "fail to execute\n");
                return 1;
            } else if(pid == 0){

                // TODO: execvp에서 execv로 변경
                char *args[] = {parse_inst->instruction, NULL};  

                if(execv(args[0], args) == -1){
                    // execvp의 반환 값에 따라서, 명령 실패 이유를 찾도록 한다.
                    perror("execvp - fail to run the command : ");
                    exit(EXIT_FAILURE); 
                }     
            } else {
                wait(NULL);
            }
            free_parsed_instruction(parse_inst);
            /*
            switch(parse_inst->delimiter){
                case '|':
                    // pipe
                    break;
                case '>':
                    // redirection
                    break;
                default:
                    // normal execution
                    break;
            }
            */
        }

        // 파이핑 파서 처리할 때, 파이핑 format 배열을 생성해서 반복 처리할 수 있게 하기
        // inst A, | , inst B 구조로 파이핑 구조체 생성
        // 두 번째 명령어 부터는 instA는 특수 문자열로 무시 처리
    
        // redirect 처리할 때는 단순 Inst A > file 형태로 처리

        // Parser 반복 호출을 통해서 Instruction A, B, C를 점진적으로 처리하는 방식으로 갈지
        // pipe & redirection에서 File Descriptor를 생성 -> fork 후 상속
        // pipe ~ /tmp 디렉터리에서 파일 생성
        // redirect ~ 파일 경로 위치에 생성 -> 파일 명이 명시되지 않는 경우 Error 트리거
        // pipe의 경우에는, old_temp와 new_temp를 생성하여 다음 프로세스가 원본 데이터를 수정하지 않도록 한다. 

        // fork 과정을 while loop으로 처리하여, 연속 파이핑 처리할 수 있도록 구성
        free_parser(state);
    }
    
    return 0;
}