#include "instruction_parser.h"
#include <string.h>
#include <stdlib.h>

// instrcution parser split out two instructions between delimiter
// such as, echo "hello world" > log.filee

// this parser split two instruction between "|"
// the parser concerns about only a pair of pipeline, even there are more further code existing.
// Thus, it returns three of operands
// feeding instruction A, fed instruction B, remains

// there is the exceptional case for the quote
// if the remain string does not have instruction, it returns 0
ParsedInstruction* parse_next_instruction(ParserState *state) {
    if (state->input[state->current_pos] == '\0') {
        return NULL; 
    }

    ParsedInstruction *parsed_inst = (ParsedInstruction *)malloc(sizeof(ParsedInstruction));
    parsed_inst->instruction = (char *)malloc(strlen(state->input) + 1);
    parsed_inst->delimiter = '\0'; 
    int res_index = 0;

    for (; state->input[state->current_pos] != '\0'; state->current_pos++) {
        char current_char = state->input[state->current_pos];

        if (current_char == '"' || current_char == '\'') {
            if (!is_empty(state->stack) && state->stack->data[state->stack->top] == current_char) {
                pop(state->stack);
            } else {
                push(state->stack, current_char);
            }
        } else if ((current_char == '|' || current_char == '>') && is_empty(state->stack)) {
            // this ends when the delimiter ( | , > ) is found
            parsed_inst->delimiter = current_char;
            state->current_pos++;  // 구분자를 지나서 다음 위치로 이동
            break;
        }

        parsed_inst->instruction[res_index++] = current_char;
    }

    parsed_inst->instruction[res_index] = '\0';
    return parsed_inst;
}

ParserState* init_parser(const char *input) {
    ParserState *state = (ParserState *)malloc(sizeof(ParserState));
    state->input = input;
    state->current_pos = 0;
    state->stack = create_stack(strlen(input));
    return state;
}


void free_parser(ParserState *state) {
    free_stack(state->stack);
    free(state);
}


void free_parsed_instruction(ParsedInstruction *parsed_inst) {
    free(parsed_inst->instruction);
    free(parsed_inst);
}