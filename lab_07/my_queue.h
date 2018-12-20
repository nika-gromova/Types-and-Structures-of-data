#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#define MAX_QUEUE_LEN 100
typedef struct queue_array_struct
{
    int cur_count;
    int size;
    int in;
    int out;
    int data[MAX_QUEUE_LEN];
}queue_array_d;

int push_arr(queue_array_d *queue, int value);
int pop_arr(queue_array_d *queue, int *pop_value);

#endif // MY_QUEUE_H
