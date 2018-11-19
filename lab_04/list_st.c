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

list_stack_node *get_last(list_stack_node *head)
{
    if (head == NULL)
        return NULL;
    while (head->next)
        head = head->next;
    return head;
}

list_stack_node *push_list(list_stack_node **head, int value)
{
    list_stack_node *in = malloc(sizeof(list_stack_node));
    if (in)
    {
        in->data = value;
        in->next = NULL;
        list_stack_node *last = get_last(*head);
        if (last)
        {
            last->next = in;
        }
        else
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

list_stack_node *pop_list(list_stack_node **head)
{
    if (*head == NULL)
    {
        printf("\nStack_list is empty.\n\n");
        return NULL;
    }
    list_stack_node *tmp = *head;
    list_stack_node *prev = tmp;
    while (tmp->next)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == *head)
        *head = NULL;
    prev->next = NULL;
    return tmp;
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

/*void task_list(list_stack_node *head)
{
    if (head == NULL)
    {
        printf("\nStack_list is empty.\n");
        return;
    }
    list_stack_node *pop_first = pop_list(&head);
    printf("%d ", pop_first->data);
    list_stack_node *pop_second = NULL;
    while (head)
    {
        pop_second = pop_list(&head);
        if (pop_second)
        {
            if (pop_second->data > pop_first->data)
                printf("%d ", pop_second->data);
            else
                printf("\n%d ", pop_second->data);
            pop_first = pop_second;
        }
        else
            return;
    }
    printf("\nFinished!\n\n");
}
*/

list_stack_node *return_last(list_stack_node *head, list_stack_node *last)
{
    if (head == NULL || head == last)
        return NULL;
    list_stack_node *tmp = head;
    while (tmp->next != last)
        tmp = tmp->next;
    return tmp;
}
void task_list(list_stack_node *head)
{
    if (head == NULL)
    {
        printf("\nStack_list is empty.\n");
        return;
    }
    list_stack_node *pop_first = return_last(head, NULL);
    printf("%d ", pop_first->data);
    list_stack_node *pop_second = NULL;
    while (return_last(head, pop_first))
    {
        pop_second = return_last(head, pop_first);
        if (pop_second)
        {
            if (pop_second->data > pop_first->data)
                printf("%d ", pop_second->data);
            else
                printf("\n%d ", pop_second->data);
            pop_first = pop_second;
        }
        else
            return;
    }
    printf("\nFinished!\n\n");
}
