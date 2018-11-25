#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "my_types.h"
#include "queue_array.h"
#include "queue_list.h"

int main(void)
{
    queue_array_d *queue_arr = NULL;
    queue_list_d *queue_list = NULL;

    int rc;
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
    return 0;
}
