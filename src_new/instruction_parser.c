#include "instruction_parser.h"
#include <string.h>
#include <stdlib.h>

// instrcution parser split out two instructions and further between delimiter
// such as, echo "hello world" > log.file
// cat file | grep hello > log.file

// this parser split two instruction between "|" and ">"
// the parser concerns about only a pair of pipeline, even there are more further code existing.
// Thus, the return just includes instruction and delimeter
// After, the ParserState moves to second instruction

// there is the exceptional case for the quote
// if the remain string does not have instruction, it returns 0
parsed_instruction* parse_next_instruction(parser_state *state) {
    if (state->input[state->current_pos] == '\0') {
        return NULL; 
    }

    parsed_instruction *parsed_inst = (parsed_instruction *)malloc(sizeof(parsed_instruction));
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
            // set the ParserInstruction
            parsed_inst->delimiter = current_char;
            state->current_pos++;
            break;
        }

        parsed_inst->instruction[res_index++] = current_char;
    }

    parsed_inst->instruction[res_index] = '\0';
    return parsed_inst;
}

parser_state* init_parser(const char *input) {
    parser_state *state = (parser_state *)malloc(sizeof(parser_state));
    state->input = input;
    state->current_pos = 0;
    state->stack = create_stack(strlen(input));
    return state;
}


void free_parser(parser_state *state) {
    free_stack(state->stack);
    free(state);
}


void free_parsed_instruction(parsed_instruction *parsed_inst) {
    free(parsed_inst->instruction);
    free(parsed_inst);
}