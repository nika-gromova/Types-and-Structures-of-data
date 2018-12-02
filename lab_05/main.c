#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "defines.h"
#include "my_types.h"
#include "queue_array.h"
#include "queue_list.h"
#include "io.h"

#define MAX_PROCESSING 3000
#define CUR_CONDITION 100

double get_rand_time(double t1, double t2)
{
    // переменные для генерирования случайного значения времени
    double cur_time, random_t;
    random_t = (double)(rand())/RAND_MAX;
    cur_time = (t2 - t1) * random_t + t1;
    return cur_time;
}

unsigned long long tick(void)
{
    unsigned long d;
    __asm__ __volatile__ ("rdtsc" : "=A"(d));
    return d;
}

int computing(time_interval t_q1, time_interval t_q2)
{
    // первая очередь в виде массива и в виде стека
    queue_array_d *queue_arr_1 = NULL;
    queue_list_d *queue_list_1 = NULL;
    // вторая очередь в виде массива и в виде стека
    queue_array_d *queue_arr_2 = NULL;
    queue_list_d *queue_list_2 = NULL;

    int rc = OK;

    rc = create_queue_arr(&queue_arr_1, MAX_PROCESSING);
    if (rc == OK)
    {
        rc = create_queue_arr(&queue_arr_2, MAX_PROCESSING);
        if (rc == OK)
        {
            rc = create_queue_list(&queue_list_1, MAX_PROCESSING);
            if (rc == OK)
            {
                rc = create_queue_list(&queue_list_2, MAX_PROCESSING);
                if (rc != OK)
                    return MEMORY_ERROR;
            }
            else
                return MEMORY_ERROR;
        }
        else
            return MEMORY_ERROR;
    }
    else
        return MEMORY_ERROR;
    // количество вошедших в систему элементов первого и второго типа
    int count_in_1 = 0, count_in_2 = 0;
    // количество вышедших из системы элементов первого и второго типа
    int count_out_1 = 0, count_out_2 = 0;
    //
    int now_in_queue_1 = 0, now_in_queue_2 = 0;
    //
    int sum_in_queue_1 = 0, sum_in_queue_2 = 0;
    // общее время прихода для элементов первого и второго типа
    double time_arrival_1 = 0, time_arrival_2 = 0;
    // общее время простоя ОА
    double offtime = 0;
    // общее время обработки элементов первого и второго типа
    double time_total_processing = 0;
    //
    double time_total_processing_1 = 0, time_total_processing_2 = 0;
    // общее время нахождения в очереди
    double time_total_waiting_1 = 0, time_total_waiting_2 = 0;
    // общее время моделирования всей системы
    double total_modeling_time = 0;

    double t1 = 0, t2 = 0, tproc = 0, tinit = -1;
    int type = 0;
    int count_avg = 0;
    int flag = 1;
    int flag_do_1 = -1;

    // расчетное время моделирования всей системы
    double estimated_total_modeling_time = 0;

    double tmp1, tmp2, prev = 0, procprev = 0;

    t1 = get_rand_time(t_q1.start_in, t_q1.end_in);
    t2 = get_rand_time(t_q2.start_in, t_q2.end_in);

    time_arrival_1 += t1;
    rc = push_arr(queue_arr_1, time_arrival_1);
    if (rc != OK)
    {
        printf("Queue overflow\n");
        return rc;
    }
    count_in_1++;
    now_in_queue_1++;

    time_arrival_2 += t2;
    rc = push_arr(queue_arr_2, time_arrival_2);
    if (rc != OK)
    {
        printf("Queue overflow\n");
        return rc;
    }
    count_in_2++;
    now_in_queue_2++;


    while (count_out_1 < 1000)
    {
        if (type == 1 || flag == 1)
        {
            rc = pop_arr(queue_arr_1, &tmp1);
            if (rc != OK)
            {
                if (pop_arr(queue_arr_2, &tmp2) == OK || tmp2 != -1)
                    flag_do_1 = 0; // КОСТЫЛЬ ГИГАНТСКИЙ
                else
                    rc = EMPTY;
            }
        }
        if (type == 2 || flag == 1)
        {
            rc = pop_arr(queue_arr_2, &tmp2);
            if (rc != OK)
            {
                if (pop_arr(queue_arr_1, &tmp1) == OK || tmp1 != -1)
                    flag_do_1 = 1; // КОСТЫЛЬ ГИГАНТСКИЙ 2.0
                else
                    rc = EMPTY;
            }
        }
        flag = 0;
        if (tinit < 0)
            tinit = (time_arrival_1 <= time_arrival_2) ? time_arrival_1 : time_arrival_2;
        //printf("%.2lf %.2lf rc = %d ", tmp1, tmp2, rc);
        if (rc != EMPTY)
        {
            if (flag_do_1 == 1 || (tmp1 <= tmp2 && tmp1 > 0 && tmp2 > 0))
            {
                tproc = get_rand_time(t_q1.start_proc, t_q1.end_proc);
                //printf("%.2lf (1)", tproc);
                type = 1;
                count_out_1++;
                offtime += ((procprev - fabs(tmp1 - prev)< 0) ? (fabs(procprev - fabs(tmp1 - prev))) : 0);
                time_total_waiting_1 += ((procprev - (tmp1 - prev) > 0) ? (procprev - (tmp1 - prev)) : 0);
                time_total_processing += tproc;
                time_total_processing_1 += tproc;
                procprev = tproc;
                prev = tmp1;
                now_in_queue_1--;
                tmp1 = -1;
            }
            else if (flag_do_1 == 0 || (tmp1 > tmp2 && tmp1 > 0 && tmp2 > 0))
            {
                tproc = get_rand_time(t_q2.start_proc, t_q2.end_proc);
                //("%.2lf (2)", tproc);
                type = 2;
                count_out_2++;
                offtime += ((procprev - fabs(tmp2 - prev) < 0) ? (fabs(procprev - fabs(tmp2 - prev))) : 0);
                time_total_waiting_2 += ((procprev - (tmp2 - prev) > 0) ? (procprev - (tmp2 - prev)) : 0);
                time_total_processing += tproc;
                time_total_processing_2 += tproc;
                procprev = tproc;
                prev = tmp2;
                now_in_queue_2--;
                tmp2 = -1;
            }
        }
        else
            flag = 1;

        t1 = get_rand_time(t_q1.start_in, t_q1.end_in);
        t2 = get_rand_time(t_q2.start_in, t_q2.end_in);
        //printf("new generated (1) = %.2lf, new generated(2) = %.2lf ", time_arrival_1 + t1, time_arrival_2 + t2);
        if (time_total_processing + tinit + 5000 >= time_arrival_1 + t1 || flag == 1)
        {
            time_arrival_1 += t1;
            rc = push_arr(queue_arr_1, time_arrival_1);
            if (rc != OK)
            {
                printf("Queue overflow\n");
                return rc;
            }
            //printf(" *%.2lf* was pushed_1 ", time_arrival_1);
            count_in_1++;
            now_in_queue_1++;
        }
        if (time_total_processing + tinit + 5000 >= time_arrival_2 + t2 || flag == 1)
        {
            time_arrival_2 += t2;
            rc = push_arr(queue_arr_2, time_arrival_2);
            if (rc != OK)
            {
                printf("Queue overflow\n");
                return rc;
            }
            //printf(" *%.2lf* was pushed_2 ", time_arrival_2);
            count_in_2++;
            now_in_queue_2++;
        }
        //printf("flag = %d\n", flag);

        //printf("%d %d\n", now_in_queue_1, now_in_queue_2);
        sum_in_queue_1 += now_in_queue_1;
        sum_in_queue_2 += now_in_queue_2;
        count_avg++;
        if (count_out_1 % 100 == 0 && count_out_1 != 0)
        {
            printf("%d.\n", count_out_1);
            printf("Current length of FIRST queue: %d\n", now_in_queue_1);
            printf("Current length of SECOND queue: %d\n", now_in_queue_2);
            printf("Average length of FIRST queue: %.2lf\n", (double)(sum_in_queue_1 / count_avg));
            printf("Average length of SECOND queue: %.2lf\n", (double)(sum_in_queue_2 / count_avg));
            printf("Number of IN elemnets of FIRST queue: %d\n", count_in_1);
            printf("Number of IN elemnets of SECOND queue: %d\n", count_in_2);
            printf("Number of OUT elemnets of FIRST queue: %d\n", count_out_1);
            printf("Number of OUT elemnets of SECOND queue: %d\n\n", count_out_2);
        }
    }
    tmp1 = ((t_q1.start_proc + t_q1.end_proc) / 2) * count_out_1 + ((t_q2.start_proc + t_q2.end_proc) / 2) * count_out_2;
    tmp2 = ((t_q1.start_in + t_q1.end_in) / 2) * count_in_1 + ((t_q2.start_in + t_q2.end_in) / 2) * count_in_2;
    estimated_total_modeling_time = (tmp1 > tmp2) ? (tmp1) : (tmp2);

    tmp1 = time_total_processing;
    tmp2 = (time_arrival_1 + time_arrival_2);
    total_modeling_time = (tmp1 > tmp2) ? (tmp1) : (tmp2);
    printf("---------------\n\n%.2lf\n%.2lf\n", estimated_total_modeling_time, total_modeling_time);
    printf("\n%d %d\n", count_in_1, count_in_2);
    printf("%.2lf %.2lf\n", time_arrival_1 / ((t_q1.start_in + t_q1.end_in) / 2), time_arrival_2 / ((t_q2.start_in + t_q2.end_in) / 2));
    printf("%.2lf\n", offtime);
    printf("%.2lf\n", time_total_processing + offtime);
    free(queue_arr_1->data);
    free(queue_arr_1);
    free(queue_arr_2->data);
    free(queue_arr_2);
    return OK;
}

int main(void)
{
    srand(time(NULL));
    char buf[10];
    int count_line;
    char choice;
    time_interval time_q1 = { 1, 5, 0, 4 }, time_q2 = { 0, 3, 0, 1 };

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
    printf("\n%s\n\n", (choice == 1) ? "You would like to change the parameters..." : "You don't want to change anything.");

    if (choice == 1)
    {
        double tmp1, tmp2;
        rc = INCORRECT_INPUT;
        while (rc == INCORRECT_INPUT)
        {
            printf("\nInput start and end of time IN interval for FIRST queue. Format: t1 t2, t1 < t2\n");
            rc = read_2double(buf, sizeof(buf), &tmp1, &tmp2);
            if (rc == OK)
            {
                if (tmp1 < tmp2)
                {
                    time_q1.start_in = tmp1;
                    time_q1.end_in = tmp2;
                }
                else
                {
                    printf("Incorrect input :( Try again.");
                    rc = INCORRECT_INPUT;
                }
            }
            else
                printf("Incorrect input :( Try again.");
        }
        rc = INCORRECT_INPUT;
        while (rc == INCORRECT_INPUT)
        {
            printf("\nInput start and end of time IN interval for SECOND queue. Format: t1 t2, t1 < t2\n");
            rc = read_2double(buf, sizeof(buf), &tmp1, &tmp2);
            if (rc == OK)
            {
                if (tmp1 < tmp2)
                {
                    time_q2.start_in = tmp1;
                    time_q2.end_in = tmp2;
                }
                else
                {
                    printf("Incorrect input :( Try again.");
                    rc = INCORRECT_INPUT;
                }
            }
            else
            {
                printf("Incorrect input :( Try again.");
                rc = INCORRECT_INPUT;
            }
        }
        rc = INCORRECT_INPUT;
        while (rc == INCORRECT_INPUT)
        {
            printf("\nInput start and end of time of PROCESSING interval for FIRST queue. Format: t1 t2, t1 < t2\n");
            rc = read_2double(buf, sizeof(buf), &tmp1, &tmp2);
            if (rc == OK)
            {
                if (tmp1 < tmp2)
                {
                    time_q2.start_proc = tmp1;
                    time_q2.end_proc = tmp2;
                }
                else
                {
                    printf("Incorrect input :( Try again.");
                    rc = INCORRECT_INPUT;
                }
            }
            else
            {
                printf("Incorrect input :( Try again.");
                rc = INCORRECT_INPUT;
            }
        }
        rc = INCORRECT_INPUT;
        while (rc == INCORRECT_INPUT)
        {
            printf("\nInput start and end of time of PROCESSING interval for SECOND queue. Format: t1 t2, t1 < t2\n");
            rc = read_2double(buf, sizeof(buf), &tmp1, &tmp2);
            if (rc == OK)
            {
                if (tmp1 < tmp2)
                {
                    time_q2.start_proc = tmp1;
                    time_q2.end_proc = tmp2;
                }
                else
                {
                    printf("Incorrect input :( Try again.");
                    rc = INCORRECT_INPUT;
                }
            }
            else
            {
                printf("Incorrect input :( Try again.");
                rc = INCORRECT_INPUT;
            }
        }
        printf("%.2lf, %.2lf, %.2lf, %.2lf\n", time_q1.start_in, time_q2.start_in, time_q1.end_in, time_q2.end_in);
    }

    rc = computing(time_q1, time_q2);
    if (rc != OK)
        printf("\nrc = %d\n", rc);


    /*int i;
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
    }*/
    return OK;
}
