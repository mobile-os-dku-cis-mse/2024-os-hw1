//
// Created by user on 2024-09-19.
//
#include "./tools/stack.h"


#ifndef INC_2024_OS_HW1_INSTRUCTION_PARSER_H
#define INC_2024_OS_HW1_INSTRUCTION_PARSER_H

typedef struct {
    const char *input;
    int current_pos;
    Stack *stack;
} ParserState;

typedef struct {
    char *instruction;
    char delimiter;
} ParsedInstruction;

ParsedInstruction* parse_next_instruction(ParserState *state);
ParserState* init_parser(const char *input);
void free_parser(ParserState *state);
void free_parsed_instruction(ParsedInstruction *parsed_inst);
#endif //INC_2024_OS_HW1_INSTRUCTION_PARSER_H