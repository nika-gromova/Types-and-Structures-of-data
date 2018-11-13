#ifndef TYPES_H
#define TYPES_H

typedef int Type;
typedef struct stack_array_tag Stack_arr;
struct stack_array_tag
{
    Type *data;
    size_t size;
    size_t top;
};

typedef struct stack_list_tag Stack_list;
struct stack_list_tag
{
    Type *data;
    Stack_list *next;
}
#endif // TYPES_H
