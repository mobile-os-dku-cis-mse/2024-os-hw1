//
// Created by user on 2024-09-19.
//

#ifndef INC_2024_OS_HW1_INSTRUCTION_PARSER_H
#define INC_2024_OS_HW1_INSTRUCTION_PARSER_H
#include "./tools/stack.h"

typedef struct {
    const char *input;
    int current_pos;
    Stack *stack;
} parser_state;

typedef struct {
    char *instruction;
    char delimiter;
} parsed_instruction;

parsed_instruction* parse_next_instruction(parser_state *state);
parser_state* init_parser(const char *input);
void free_parser(parser_state *state);
void free_parsed_instruction(parsed_instruction *parsed_inst);
#endif //INC_2024_OS_HW1_INSTRUCTION_PARSER_H