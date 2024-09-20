//
// Created by user on 2024-09-19.
//

#ifndef INC_2024_OS_HW1_INSTRUCTION_PARSER_H
#define INC_2024_OS_HW1_INSTRUCTION_PARSER_H

typedef struct _piped_operands{
    char *inst_a;
    char *inst_b;
    char *remainder;
}Piped_operands;

int pipe_parser(char * string, Piped_operands ret);
#endif //INC_2024_OS_HW1_INSTRUCTION_PARSER_H
