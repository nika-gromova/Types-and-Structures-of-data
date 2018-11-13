#include "types.h"
#include "defines.h"

#define INIT_SIZE 10
#define REALLOC_MULT 2

#include <stdio.h>
#include <stdlib.h>

Stack_arr *create_stack_arr(void)
{
    Stack_arr *out = malloc(sizeof(Stack_arr));
    if (!out)
    {
        printf("Memory error occured while allocating memory for stack.\n");
        return NULL;
    }
    out->size = INIT_SIZE;
    out->data = calloc(INIT_SIZE, sizeof(Type));
    if (!out->data)
    {
        free(out);
        printf("Memory error occured while allocating memory for data in stack.\n");
        return NULL;
    }
    out->top = 0;
    return out;
}

void free_stack_arr(Stack_arr *stack)
{
    free(stack->data);
    free(stack);
}

Stack_arr *pop_arr(Stack_arr *stack)
{
    if (stack->top == 0)
    {
        printf("Stack is empty.\n");
        return NULL;
    }
    stack->top--;
    return *(stack->data[stack->top]);
}

Stack_arr *peek_arr(Stack_arr *stack)
{
    if (stack->top == 0)
    {
        printf("Stack is empty.\n");
        return NULL;
    }
    return *(stack->data[stack->top - 1]);
}

