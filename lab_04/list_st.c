#include <stdio.h>
#include <stdlib.h>
#include "my_types.h"

void delete_stack_list(list_stack_node *head)
{
    list_stack_node *tmp;
    for (; head; head = tmp)
    {
        tmp = head->next;
        free(head);
    }
}

list_stack_node *push_list(list_stack_node **head, int value)
{
    list_stack_node *in = malloc(sizeof(list_stack_node));
    if (in)
    {
        in->data = value;
        in->next = *head;
        *head = in;
        return in;
    }
    else
    {
        printf("\nError while creating a stack_list element.\n\n");
        delete_stack_list(*head);
        *head = NULL;
        return NULL;
    }
}

int pop_list(list_stack_node **head, list_stack_node **address, int *rc)
{
    if (*head == NULL)
    {
        *rc = -1;
        return -1;
    }
    int pop_value;
    list_stack_node *tmp = *head;
    *head = (*head)->next;
    pop_value = tmp->data;
    *address = tmp;
    free(tmp);
    *rc = 0;
    return pop_value;
}


void print_stack_list(list_stack_node *head)
{
    if (head == NULL)
    {
        printf("\nStack_list is empty.\n");
        return;
    }
    printf("Stack_list:\n");
    while (head)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n\n");
}

void task_list(list_stack_node **head)
{
    if (*head == NULL)
    {
        printf("\nStack_list is empty.\n");
        return;
    }
    int rc = 0;
    list_stack_node *address = NULL;;
    int pop_first = pop_list(head, &address, &rc);
    printf("%d ", pop_first);
    int pop_second;
    while (*head != NULL)
    {
        pop_second = pop_list(head, &address, &rc);
        if (pop_second > pop_first)
            printf("%d ", pop_second);
        else
            printf("\n%d ", pop_second);
        pop_first = pop_second;
    }
    printf("\nFinished!\n\n");
}
