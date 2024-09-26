#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Stack 구조체 정의
typedef struct {
    char *data;
    int top;
    int size;
} Stack;

// Stack 초기화
Stack* create_stack(int size) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->data = (char *)malloc(size * sizeof(char));
    stack->top = -1;
    stack->size = size;
    return stack;
}

// Stack 푸시
void push(Stack *stack, char ch) {
    if (stack->top < stack->size - 1) {
        stack->data[++stack->top] = ch;
    }
}

// Stack 팝
char pop(Stack *stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    }
    return '\0';
}

// Stack이 비어 있는지 확인
int is_empty(Stack *stack) {
    return stack->top == -1;
}

// Stack 해제
void free_stack(Stack *stack) {
    free(stack->data);
    free(stack);
}

// 지속적인 파싱을 위해 입력 상태를 저장할 구조체
typedef struct {
    const char *input;
    int current_pos;
    Stack *stack;
} ParserState;

// 파이프 구분자 '|'를 무시하고 한 번에 하나의 instruction을 반환하는 파싱 함수
char* parse_next_instruction(ParserState *state, char delimiter) {
    if (state->input[state->current_pos] == '\0') {
        return NULL;  // 문자열의 끝에 도달하면 NULL 반환
    }

    char *result = (char *)malloc(strlen(state->input) + 1);
    int res_index = 0;
    
    for (; state->input[state->current_pos] != '\0'; state->current_pos++) {
        char current_char = state->input[state->current_pos];

        if (current_char == '"' || current_char == '\'') {
            // 문자열 리터럴 구분을 위해 스택에 따옴표를 푸시 또는 팝
            if (!is_empty(state->stack) && state->stack->data[state->stack->top] == current_char) {
                pop(state->stack);
            } else {
                push(state->stack, current_char);
            }
        } else if (current_char == delimiter && is_empty(state->stack)) {
            // 스택이 비어 있는 경우에만 구분자로 처리 (명령어 구분)
            state->current_pos++;  // 구분자 이후의 위치로 이동
            break;  // 명령어 종료
        }

        result[res_index++] = current_char;  // 구분자를 무시하고 문자를 복사
    }

    result[res_index] = '\0';
    return result;
}

// 파서 초기화 함수
ParserState* init_parser(const char *input) {
    ParserState *state = (ParserState *)malloc(sizeof(ParserState));
    state->input = input;
    state->current_pos = 0;
    state->stack = create_stack(strlen(input));
    return state;
}

// 파서 상태 해제
void free_parser(ParserState *state) {
    free_stack(state->stack);
    free(state);
}

int main() {
    const char *input = "echo \"this | is | a | test\" | grep test | sort";
    ParserState *state = init_parser(input);

    char *instruction;
    while ((instruction = parse_next_instruction(state, '|')) != NULL) {
        printf("Instruction: %s\n", instruction);
        free(instruction);  // 동적으로 할당된 메모리 해제
    }

    free_parser(state);  // 파서 상태 해제
    return 0;
}

