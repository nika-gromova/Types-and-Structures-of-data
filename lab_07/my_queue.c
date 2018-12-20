#include <stdlib.h>

#include "my_queue.h"
#include "defines.h"

int push_arr(queue_array_d *queue, int value)
{
    if (queue->cur_count == queue->size)
    {
        return QUEUE_OWERFLOW;
    }
    if (queue->in == queue->size)
    {
        queue->in = 0;
    }
    queue->data[queue->in] = value;
    (queue->in)++;
    (queue->cur_count)++;
    return OK;
}

int pop_arr(queue_array_d *queue, int *pop_value)
{
    if (queue->cur_count == 0)
    {
        return QUEUE_UNDERFLOW;
    }
    if (queue->out == queue->size)
    {
        queue->out = 0;
    }
    *pop_value = queue->data[queue->out];
    (queue->out)++;
    (queue->cur_count)--;
    return OK;
}
