#include <stdlib.h>
#include <stdio.h>
#include "defines.h"
#include "my_types.h"
#include "queue_list.h"

void free_list(queue_list_n *head)
{
    queue_list_n *tmp;
    for (; head; head = tmp)
    {
        tmp = head->next;
        free(head);
    }
}

int create_queue_list(queue_list_d **queue, int limit)
{
    queue_list_d *out = malloc(sizeof(queue_list_d));
    if (!out)
        return MEMORY_ERROR;
    out->cur_count = 0;
    out->size = limit;
    out->head = NULL;
    out->tail = NULL;
    *queue = out;
    return OK;
}

int push_list(queue_list_d *queue, double value)
{
    if (queue->cur_count == queue->size)
        return QUEUE_OWERFLOW;
    queue_list_n *out = malloc(sizeof(queue_list_n));
    if (!out)
    {
        free(queue->head);
        free(queue);
        return MEMORY_ERROR;
    }
    out->time = value;
    out->next = NULL;
    (queue->cur_count)++;
    if (queue->head == NULL)
    {
        queue->tail = out;
        queue->head = out;
    }
    else
    {
        (queue->tail)->next = out;
        (queue->tail) = out;
    }
    return OK;
}

int pop_list(queue_list_d *queue, double *pop_value)
{
    if (queue->cur_count == 0)
        return QUEUE_UNDERFLOW;
    if (queue->head == NULL)
        return QUEUE_UNDERFLOW;
    queue_list_n *out = queue->head;
    queue->head = queue->head->next;
    *pop_value = out->time;
    free(out);
    (queue->cur_count)--;
    return OK;
}
