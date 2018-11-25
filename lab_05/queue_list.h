#ifndef QUEUE_LIST_H
#define QUEUE_LIST_H

#include "my_types.h"

int pop_list(queue_list_d *queue, double *pop_value);
int push_list(queue_list_d *queue, double value);
int create_queue_list(queue_list_d **queue, int limit);
void free_list(queue_list_n *head);

#endif // QUEUE_LIST_H
