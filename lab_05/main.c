#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "my_types.h"
#include "queue_array.h"
#include "queue_list.h"
#include "io.h"

int main(void)
{
    char buf[10];
    int count_line;
    char choice;

    queue_array_d *queue_arr = NULL;
    queue_list_d *queue_list = NULL;
    /*
    int count_in_1 = 0, count_in_2 = 0;
    int count_out_1 = 0, count_out_2 = 0;
    double time_interval_1_start = 1, time_interval_1_end = 5;
    double time_interval_2_start = 0, time_interval_2_end = 3;
    double time_processing_1_start = 0, time_processing_1_end = 4;
    double time_processing_2_start = 0, time_processing_1_end = 1;
    double cur_time, random_t;
    double time_arrival_1 = 0, time_arrival_2 = 0;
    double offtime_1 = 0, offtime_2 = 0;
    double time_total_processing_1 = 0, time_total_processing_2 = 0;
    double total_modeling_time = 0;

    double estimated_total_modeling_time = 0;
    */

    int rc = INCORRECT_INPUT;

    printf("Hello! This is a programme simulating the work of one serving device with two queues. The first one has more priority.\n");
    printf("The initial time of arriving for the first queque is [1,5] and for the second is [0,3]\n");
    printf("The initial time of processing for the first queque is [0,4] and for the second is [0,1]\n");
    printf("Please, input 'y', if you want to change the initial conditions.\n");
    printf("Input 'n', if you want to continue with initial parameters\n\n");

    while (rc == INCORRECT_INPUT)
    {
        count_line = read_line(buf, sizeof(buf));
        if (count_line == 0)
        {
            printf("Incorrect input, please try again.\n");
            rc = INCORRECT_INPUT;
        }
        else
        {
            if (strcmp(buf, "y") == 0)
            {
                choice = 1;
                rc = OK;
            }
            else if (strcmp(buf, "n") == 0)
            {
                choice = 0;
                rc = OK;
            }
            else
            {
                printf("Incorrect input, please try again.\n");
                rc = INCORRECT_INPUT;
            }
        }
    }
    printf("Change: %s\n", (choice == 1) ? "YES" : "NO");

    int i;
    double pop_value;
    rc = create_queue_arr(&queue_arr, 10);
    if (rc == OK)
    {
        printf("Created\n");
        for (i = 0; i < 10 && rc == OK; i++)
        {
            rc = push_arr(queue_arr, i);
        }
        printf("Pushed %d elements\n", i);
        printf("Pushed one more element: %s\n", ((rc = push_arr(queue_arr, 10)) == QUEUE_OWERFLOW) ? "NO" : "YES");
        for (int k = 0; k < queue_arr->cur_count; k++)
            printf("%.2lf ", queue_arr->data[k]);
        rc = OK;
        for (int j = 0; j < 10 && rc == OK; j++)
        {
            rc = pop_arr(queue_arr, &pop_value);
            printf("\nElement %.2lf was popped", pop_value);
        }
        printf("\nPopped one more element: %s\n", ((rc = pop_arr(queue_arr, &pop_value)) == QUEUE_UNDERFLOW) ? "NO" : "YES");
        free(queue_arr->data);
        free(queue_arr);
    }
    printf("\nLIST:\n\n");
    rc = create_queue_list(&queue_list, 10);
    if (rc == OK)
    {
        printf("Created\n");
        for (i = 0; i < 10 && rc == OK; i++)
        {
            rc = push_list(queue_list, i);
        }
        printf("Pushed %d elements\n", i);
        printf("Pushed one more element: %s\n", ((rc = push_list(queue_list, 10)) == QUEUE_OWERFLOW) ? "NO" : "YES");

        rc = OK;
        for (int j = 0; j < 10 && rc == OK; j++)
        {
            rc = pop_list(queue_list, &pop_value);
            printf("\nElement %.2lf was popped", pop_value);
        }
        printf("\nPopped one more element: %s\n", ((rc = pop_list(queue_list, &pop_value)) == QUEUE_UNDERFLOW) ? "NO" : "YES");
        free_list(queue_list->head);
        free(queue_list);
    }
    return OK;
}
