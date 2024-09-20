#include "instruction_parser.h"
#include <string.h>

// instrcution parser split out two instructions between delimiter
// such as, echo "hello world" > log.filee

// this parser split two instruction between "|"
// the parser concerns about only a pair of pipeline, even there are more further code existing.
// Thus, it returns three of operands
// feeding instruction A, fed instruction B, remains
int pipe_parser(char * string, Piped_operands ret){
    ret.inst_a = strtok(string, "|");
    ret.inst_b = strtok(string, "|");
    ret.remainder = strtok(string, "|");
}

// this parser split an instruction and file
int redirect_parser(char * string, Piped_operands ret){
    ret.inst_a = strtok(string, ">");
    ret.inst_b = strtok(string, ">");
}

