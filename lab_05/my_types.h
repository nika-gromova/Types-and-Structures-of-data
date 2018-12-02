#ifndef MY_TYPES_H
#define MY_TYPES_H


typedef struct queue_array_struct
{
    int cur_count;
    int size;
    int in;
    int out;
    double *data;
}queue_array_d;

typedef struct queue_list_node
{
    double time;
    struct queue_list_node *next;
}queue_list_n;

typedef struct queue_list_struct
{
    int size;
    int cur_count;
    struct queue_list_node *head;
    struct queue_list_node *tail;
}queue_list_d;

typedef struct time_st
{
    double start_in;
    double end_in;
    double start_proc;
    double end_proc;
}time_interval;

#endif // MY_TYPES_H
