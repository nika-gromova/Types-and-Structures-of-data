#ifndef ARRAY_ST_H
#define ARRAY_ST_H
#include "my_types.h"
array_stack_t *create_stack_arr(int size);
array_stack_t *push_arr(array_stack_t *stack, int value);
void print_stack_arr(array_stack_t *stack);
int pop_arr(array_stack_t *stack, int *rc);
void task_arr(array_stack_t *stack);
void free_stack_arr(array_stack_t *stack);

#endif // ARRAY_ST_H
