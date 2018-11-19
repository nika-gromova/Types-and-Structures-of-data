#ifndef LIST_ST_H
#define LIST_ST_H
#include "my_types.h"
void delete_stack_list(list_stack_node *head);
list_stack_node *push_list(list_stack_node **head, int value);
list_stack_node *pop_list(list_stack_node **head);
void print_stack_list(list_stack_node *head);
void task_list(list_stack_node *head);
#endif // LIST_ST_H
