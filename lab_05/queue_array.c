#include <stdlib.h>
#include "my_types.h"
#include "queue_array.h"
#include "defines.h"

int create_queue_arr(queue_array_d **queue, int limit)
{
    queue_array_d *out = malloc(sizeof(queue_array_d));
    if (!out)
        return MEMORY_ERROR;

    out->data = malloc(limit * sizeof(double));
    if (out->data == NULL)
    {
        free(out);
        return MEMORY_ERROR;
    }
    out->in = 0;
    out->out = 0;
    out->size = limit;
    out->cur_count = 0;
    *queue = out;
    return OK;
}

int push_arr(queue_array_d *queue, double value)
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

int pop_arr(queue_array_d *queue, double *pop_value)
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

