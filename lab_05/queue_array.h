#ifndef QUEUE_ARRAY_H
#define QUEUE_ARRAY_H

#include "my_types.h"

int pop_arr(queue_array_d *queue, double *pop_value);
int push_arr(queue_array_d *queue, double value);
int create_queue_arr(queue_array_d **queue, int limit);

#endif // QUEUE_ARRAY_H
