
#ifndef INC_2024_OS_HW1_STACK_H
#define INC_2024_OS_HW1_STACK_H

typedef struct {
    char *data;
    int top;
    int size;
} Stack;

void push(Stack *s, char c);
char pop(Stack *s);
char peek(Stack *s);
int is_empty(Stack *s);

Stack* create_stack(int size);
void free_stack(Stack *stack);
#endif //INC_2024_OS_HW1_STACK_H