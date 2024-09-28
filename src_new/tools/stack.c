#include "stack.h"
#include <stdlib.h>
Stack* create_stack(int size) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->data = (char *)malloc(size * sizeof(char));
    stack->top = -1;
    stack->size = size;
    return stack;
}

void push(Stack *stack, char ch) {
    if (stack->top < stack->size - 1) {
        stack->data[++stack->top] = ch;
    }
}

char pop(Stack *stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    }
    return '\0';
}

int is_empty(Stack *stack) {
    return stack->top == -1;
}

void free_stack(Stack *stack) {
    free(stack->data);
    free(stack);
}