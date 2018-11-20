#ifndef MY_TYPES_H
#define MY_TYPES_H
typedef struct array_stack_t array_stack_t;

struct array_stack_t
{
    int *data;
    int size;
    int top;
};

typedef struct list_stack_t list_stack_node;

struct list_stack_t
{
    int data;
    list_stack_node *next;
};

typedef struct list_stack list_stack_t;

struct list_stack_node
{
    int size;
    list_stack_node *last;
};

#endif // MY_TYPES_H
