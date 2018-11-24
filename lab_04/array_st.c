#include "my_types.h"
#include "array_st.h"

#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 3
#define REALLOC_MULT 2

array_stack_t *create_stack_arr(int size)
{
    array_stack_t *out = malloc(sizeof(array_stack_t));
    if (!out)
    {
        printf("Memory error occured while allocating memory for stack.\n\n");
        return NULL;
    }
    out->size = size;
    out->data = calloc(size, sizeof(int));
    if (!out->data)
    {
        free(out);
        printf("Memory error occured while allocating memory for data in stack.\n\n");
        return NULL;
    }
    out->top = 0;
    return out;
}

void free_stack_arr(array_stack_t *stack)
{
    free(stack->data);
    free(stack);
}

int pop_arr(array_stack_t *stack, int *rc)
{
    if (stack->top == 0)
    {
        *rc = -1;
        return 0;
    }
    *rc = 0;
    stack->top--;
    return ((stack->data)[stack->top]);
}

int *peek_arr(array_stack_t *stack)
{
    if (stack->top == 0)
    {
        printf("\nStack is empty.\n");
        return NULL;
    }
    return &((stack->data)[stack->top - 1]);
}

// Функция для перевыделения памяти под динамически расширяемый массив
/*
void reallocation(array_stack_t *stack)
{
    stack->size *= REALLOC_MULT;
    int *tmp = realloc(stack->data, stack->size * sizeof(int));
    if (tmp)
    {
        stack->data = tmp;
    }
    else
    {
        free_stack_arr(stack);
        stack = NULL;
    }
}
*/

// Функция для динамически расширяемого стека на массиве
/*
array_stack_t *push_arr(array_stack_t *stack, int value)
{
    if (stack->top >= stack->size)
    {
        reallocation(stack);
        if (stack == NULL)
            return NULL;
    }
    stack->data[stack->top] = value;
    (stack->top)++;
    return stack;
}
*/

array_stack_t *push_arr(array_stack_t *stack, int value)
{
    if (stack->top >= stack->size)
    {
        free(stack->data);
        return NULL;
    }
    stack->data[stack->top] = value;
    (stack->top)++;
    return stack;
}

void print_stack_arr(array_stack_t *stack)
{
    if (stack->top == 0)
    {
        printf("\nStack_array is empty.\n");
        return;
    }
    printf("Stack_array:\n");
    int *arr = stack->data;
    for (int i = stack->top - 1; i >= 0; i--)
        printf("%d ", arr[i]);
    printf("\n\n");
}

void task_arr(array_stack_t *stack)
{
    if (stack->top == 0)
    {
        printf("\nStack_array is empty.\n");
        return;
    }
    int rc;
    int cur_value = pop_arr(stack, &rc);
    if (rc == -1)
        return;
    printf("\n%d ", cur_value);
    int next;
    while (stack->top != 0)
    {
        next = pop_arr(stack, &rc);
        if (next > cur_value)
            printf("%d ", next);
        else
            printf("\n%d ", next);
        cur_value = next;
    }
    printf("\nFinished!\n\n");
}
