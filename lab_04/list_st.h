#ifndef LIST_ST_H
#define LIST_ST_H
#include "my_types.h"
void delete_stack_list(list_stack_node *head);
list_stack_node *push_list(list_stack_node **head, int value);
int pop_list(list_stack_node **head, list_stack_node **address, int *rc);
void print_stack_list(list_stack_node *head);
void task_list(list_stack_node **head, list_stack_node *free[], int *m);
void add_remove_addresses(list_stack_node *occupied[], list_stack_node *free[], int *n, int *m, list_stack_node *address);
#endif // LIST_ST_H
