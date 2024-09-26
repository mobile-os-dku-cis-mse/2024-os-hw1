
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

#endif //INC_2024_OS_HW1_STACK_H