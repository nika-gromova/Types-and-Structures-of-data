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

#define MAX_PROCESSING 5000
#define EPS 1e-7

#define IS_NULL(num) (fabs(num) <= EPS)
#define IS_EQUAL(num1, num2) (fabs((num1) - (num2)) <= EPS)

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

int computing_list(time_interval t_q1, time_interval t_q2)
{
    // первая очередь в виде списка
    queue_list_d *queue_arr_1 = NULL;

    // вторая очередь в виде списка
    queue_list_d *queue_arr_2 = NULL;

    int rc = OK;

    rc = create_queue_list(&queue_arr_1, MAX_PROCESSING);
    if (rc == OK)
    {
        rc = create_queue_list(&queue_arr_2, MAX_PROCESSING);
        if (rc != OK)
            return MEMORY_ERROR;
    }
    else
        return MEMORY_ERROR;
    // количество вошедших в систему элементов первого и второго типа
    int count_in_1 = 0, count_in_2 = 0;
    // количество вышедших из системы элементов первого и второго типа
    int count_out_1 = 0, count_out_2 = 0;
    // Переменные для подсчета средней длины очереди
    int sum_in_queue_1 = 0, sum_in_queue_2 = 0;
    int count_avg_1 = 0, count_avg_2 = 0;
    // время прихода элементов первого и второго типа, время обработки
    double time_1 = 0.0, time_2 = 0.0, time_proc = 0.0;
    // общее время работы системы
    double total_time = 0.0;
    // общее время прихода первой и второй заявок
    double time_arrival_1 = 0.0, time_arrival_2 = 0.0;
    // общее время обработки первой и второй заявок
    double total_time_processing_1 = 0.0, total_time_processing_2 = 0.0;
    // общее время простоя ОА
    double offtime = 0.0;
    // общее время нахождения в очереди
    double time_total_waiting_1 = 0.0, time_total_waiting_2 = 0.0;

    // Тип обрабатываемой заявки
    int type = 0;
    // Переменные для хранения временного результата
    double buf, pop_value;
    // Переменная для вывода промежуточного значения каждых 100 заявок первого типа
    int print_100 = 0;
    // Временная переменная для текущего минимального времени
    double t_min = 0.0;

    //
    double t1 = 0.0, t2 = 0.0;



    while (count_out_1 < 1000)
    {
        if (IS_NULL(time_1))
        {
            time_1 = get_rand_time(t_q1.start_in, t_q1.end_in);
            time_arrival_1 += time_1;
            t1 = time_1;
        }
        if (IS_NULL(time_2))
        {
            time_2 = get_rand_time(t_q2.start_in, t_q2.end_in);
            time_arrival_2 += time_2;
            t2 = time_2;
        }

        if (IS_NULL(time_proc))
        {
            if (queue_arr_1->cur_count != 0)
            {
                time_proc = get_rand_time(t_q1.start_proc, t_q1.end_proc);
                type = 1;
                pop_list(queue_arr_1, &pop_value);
                buf = total_time - pop_value;
                (buf > 0.0) ? (time_total_waiting_1 += buf) : (offtime += fabs(buf + time_proc));//
                total_time_processing_1 += time_proc;
            }
            else if (queue_arr_2->cur_count != 0)
            {
                time_proc = get_rand_time(t_q2.start_proc, t_q2.end_proc);
                type = 2;
                pop_list(queue_arr_2, &pop_value);
                buf = total_time - pop_value;
                (buf > 0.0) ? (time_total_waiting_2 += buf) : (offtime += fabs(buf + time_proc));//
                total_time_processing_2 += time_proc;
            }
        }

        if (IS_NULL(time_proc))
        {
            t_min = fmin(time_1, time_2);
        }
        else
        {
            t_min = fmin(time_1, fmin(time_2, time_proc));
        }

        if (IS_EQUAL(t_min, time_proc))
        {
            time_proc = 0.0;
            if (type == 1)
                count_out_1++;
            if (type == 2)
                count_out_2++;
        }

        if (IS_EQUAL(t_min, time_1))
        {
            //time_arrival_1 = total_time + t1;
            rc = push_list(queue_arr_1, total_time + t1);
            if (rc == OK)
            {
                count_in_1++;
                sum_in_queue_1 += queue_arr_1->cur_count;
                count_avg_1++;
            }
            else
            {
                printf("Queue overflow :(\n");
                return MEMORY_ERROR;
            }
        }
        if (IS_EQUAL(t_min, time_2))
        {
            //time_arrival_2 = total_time + t2;
            rc = push_list(queue_arr_2, total_time + t2);
            if (rc == OK)
            {
                count_in_2++;
                sum_in_queue_2 += queue_arr_2->cur_count;
                count_avg_2++;
            }
            else
            {
                printf("Queue overflow :(\n");
                return MEMORY_ERROR;
            }
        }

        time_1 -= t_min;
        time_2 -= t_min;
        if (time_proc >= t_min)
            time_proc -= t_min;
        total_time += t_min;

        if (count_out_1 % 100 == 0 && count_out_1 != print_100)
        {
            printf("%d.\n", count_out_1);
            printf("Current length of FIRST queue: %d\n", queue_arr_1->cur_count);
            printf("Current length of SECOND queue: %d\n", queue_arr_2->cur_count);
            printf("sum in 1: %d, avg = %d\n", sum_in_queue_1, count_avg_1);
            printf("Average length of FIRST queue: %.2lf\n", (double)(sum_in_queue_1 / count_avg_1));
            printf("Average length of SECOND queue: %.2lf\n", (double)(sum_in_queue_2 / count_avg_2));
            printf("Number of IN elemnets of FIRST queue: %d\n", count_in_1);
            printf("Number of IN elemnets of SECOND queue: %d\n", count_in_2);
            printf("Number of OUT elemnets of FIRST queue: %d\n", count_out_1);
            printf("Number of OUT elemnets of SECOND queue: %d\n", count_out_2);
            //printf("Total time waiting in FIRST queue: %.4lf\n", time_total_waiting_1);
            //printf("Total time waiting in SECOND queue: %.4lf\n\n", time_total_waiting_2);
            print_100 = count_out_1;
        }
    }
    double tmp;
    double avg_in_1 = (t_q1.start_in + t_q1.end_in) / 2;
    double avg_in_2 =  (t_q2.start_in + t_q2.end_in) / 2;
    double avg_out_1 = (t_q1.start_proc + t_q1.end_proc) / 2;
    double avg_out_2 = (t_q2.start_proc + t_q2.end_proc) / 2;
    printf("\n--------------------\n");
    if ((avg_in_1 + avg_in_2) >= (avg_out_1 + avg_out_2))
    {
        if (avg_in_1 < avg_in_2)
        {
            tmp = avg_in_1;
            avg_in_1 = avg_in_2;
            avg_in_2 = tmp;
        }
        printf("Estimated time IN for FIRST queue = %.2lf\n", avg_in_1 * count_in_1);
        printf("Real time IN for FIRST queue = %.2lf\n", time_arrival_1);
        printf("Margin of error: %.2lf %%\n", (fabs(avg_in_1 * count_in_1 - time_arrival_1) / (avg_in_1 * count_in_1) * 100));
        printf("Estimated time IN for SECOND queue = %.2lf\n", (avg_in_1 * count_in_1));
        printf("Real time IN for SECOND queue = %.2lf\n", time_arrival_2);
        printf("Margin of error: %.2lf %%\n", (fabs((avg_in_1 * count_in_1) - time_arrival_2) / ((avg_in_1 * count_in_1)) * 100));
        printf("Offtime: %.2lf\n", offtime);
    }
    else
    {
        double est = avg_out_1 * count_out_1 + avg_out_2 * count_out_2;
        printf("Estimated time processing = %.2lf\n", est);
        printf("Real time processing = %.2lf\n", total_time_processing_1 + total_time_processing_2);
        printf("Margin of error: %.2lf %%\n", (fabs(est - (total_time_processing_1 + total_time_processing_2)) / (est) * 100));
        printf("Offtime: %.2lf\n", offtime);
    }
    printf("Number of IN elemnets of FIRST queue: %d\n", count_in_1);
    printf("Number of IN elemnets of SECOND queue: %d\n", count_in_2);
    printf("Number of OUT elemnets of FIRST queue: %d\n", count_out_1);
    printf("Number of OUT elemnets of SECOND queue: %d\n\n", count_out_2);
    printf("\nMemory outlay for queue as an array: %d\n", (int)(sizeof(double) * MAX_PROCESSING * 2 + sizeof(queue_array_d) * 2));
    printf("Memory outlay for queue as a list: %d\n\n", (int)sizeof(queue_list_d) * 2 + (int)sizeof(queue_list_n) * (count_in_1 + count_in_2));
    //printf("Total_time: %.4lf\n", total_time);

    free(queue_arr_1);
    free(queue_arr_2);
    return OK;
}

int computing(time_interval t_q1, time_interval t_q2)
{
    // первая очередь в виде массива
    queue_array_d *queue_arr_1 = NULL;
    // вторая очередь в виде массива
    queue_array_d *queue_arr_2 = NULL;

    int rc = OK;

    rc = create_queue_arr(&queue_arr_1, MAX_PROCESSING);
    if (rc == OK)
    {
        rc = create_queue_arr(&queue_arr_2, MAX_PROCESSING);
        if (rc != OK)
            return MEMORY_ERROR;
    }
    else
        return MEMORY_ERROR;
    // количество вошедших в систему элементов первого и второго типа
    int count_in_1 = 0, count_in_2 = 0;
    // количество вышедших из системы элементов первого и второго типа
    int count_out_1 = 0, count_out_2 = 0;
    // Переменные для подсчета средней длины очереди
    int sum_in_queue_1 = 0, sum_in_queue_2 = 0;
    int count_avg_1 = 0, count_avg_2 = 0;
    // время прихода элементов первого и второго типа, время обработки
    double time_1 = 0.0, time_2 = 0.0, time_proc = 0.0;
    // общее время работы системы
    double total_time = 0.0;
    // общее время прихода первой и второй заявок
    double time_arrival_1 = 0.0, time_arrival_2 = 0.0;
    // общее время обработки первой и второй заявок
    double total_time_processing_1 = 0.0, total_time_processing_2 = 0.0;
    // общее время простоя ОА
    double offtime = 0.0;
    // общее время нахождения в очереди
    double time_total_waiting_1 = 0.0, time_total_waiting_2 = 0.0;

    // Тип обрабатываемой заявки
    int type = 0;
    // Переменные для хранения временного результата
    double buf, pop_value;
    // Переменная для вывода промежуточного значения каждых 100 заявок первого типа
    int print_100 = 0;
    // Временная переменная для текущего минимального времени
    double t_min = 0.0;

    //
    double t1 = 0.0, t2 = 0.0;



    while (count_out_1 < 1000)
    {        
        if (IS_NULL(time_1))
        {
            time_1 = get_rand_time(t_q1.start_in, t_q1.end_in);
            time_arrival_1 += time_1;
            t1 = time_1;
        }
        if (IS_NULL(time_2))
        {
            time_2 = get_rand_time(t_q2.start_in, t_q2.end_in);
            time_arrival_2 += time_2;
            t2 = time_2;
        }

        if (IS_NULL(time_proc))
        {
            if (queue_arr_1->cur_count != 0)
            {
                time_proc = get_rand_time(t_q1.start_proc, t_q1.end_proc);
                type = 1;
                pop_arr(queue_arr_1, &pop_value);
                buf = total_time - pop_value;
                (buf > 0.0) ? (time_total_waiting_1 += buf) : (offtime += fabs(buf + time_proc));//
                total_time_processing_1 += time_proc;
            }
            else if (queue_arr_2->cur_count != 0)
            {
                time_proc = get_rand_time(t_q2.start_proc, t_q2.end_proc);
                type = 2;
                pop_arr(queue_arr_2, &pop_value);
                buf = total_time - pop_value;
                (buf > 0.0) ? (time_total_waiting_2 += buf) : (offtime += fabs(buf + time_proc));//
                total_time_processing_2 += time_proc;
            }
        }

        if (IS_NULL(time_proc))
        {
            t_min = fmin(time_1, time_2);
        }
        else
        {
            t_min = fmin(time_1, fmin(time_2, time_proc));
        }

        if (IS_EQUAL(t_min, time_proc))
        {
            time_proc = 0.0;
            if (type == 1)
                count_out_1++;
            if (type == 2)
                count_out_2++;
        }

        if (IS_EQUAL(t_min, time_1))
        {
            //time_arrival_1 = total_time + t1;
            rc = push_arr(queue_arr_1, total_time + t1);
            if (rc == OK)
            {
                count_in_1++;
                sum_in_queue_1 += queue_arr_1->cur_count;
                count_avg_1++;
            }
            else
            {
                printf("Queue overflow :(\n");
                return MEMORY_ERROR;
            }
        }
        if (IS_EQUAL(t_min, time_2))
        {
            //time_arrival_2 = total_time + t2;
            rc = push_arr(queue_arr_2, total_time + t2);
            if (rc == OK)
            {
                count_in_2++;
                sum_in_queue_2 += queue_arr_2->cur_count;
                count_avg_2++;
            }
            else
            {
                printf("Queue overflow :(\n");
                return MEMORY_ERROR;
            }
        }

        time_1 -= t_min;
        time_2 -= t_min;
        if (time_proc >= t_min)
            time_proc -= t_min;
        total_time += t_min;

        if (count_out_1 % 100 == 0 && count_out_1 != print_100)
        {
            printf("%d.\n", count_out_1);
            printf("Current length of FIRST queue: %d\n", queue_arr_1->cur_count);
            printf("Current length of SECOND queue: %d\n", queue_arr_2->cur_count);
            printf("sum in 1: %d, avg = %d\n", sum_in_queue_1, count_avg_1);
            printf("Average length of FIRST queue: %.2lf\n", (double)(sum_in_queue_1 / count_avg_1));
            printf("Average length of SECOND queue: %.2lf\n", (double)(sum_in_queue_2 / count_avg_2));
            printf("Number of IN elemnets of FIRST queue: %d\n", count_in_1);
            printf("Number of IN elemnets of SECOND queue: %d\n", count_in_2);
            printf("Number of OUT elemnets of FIRST queue: %d\n", count_out_1);
            printf("Number of OUT elemnets of SECOND queue: %d\n", count_out_2);
            //printf("Total time waiting in FIRST queue: %.4lf\n", time_total_waiting_1);
            //printf("Total time waiting in SECOND queue: %.4lf\n\n", time_total_waiting_2);
            print_100 = count_out_1;
        }
    }
    double tmp;
    double avg_in_1 = (t_q1.start_in + t_q1.end_in) / 2;
    double avg_in_2 =  (t_q2.start_in + t_q2.end_in) / 2;
    double avg_out_1 = (t_q1.start_proc + t_q1.end_proc) / 2;
    double avg_out_2 = (t_q2.start_proc + t_q2.end_proc) / 2;
    printf("\n--------------------\n");
    if ((avg_in_1 + avg_in_2) >= (avg_out_1 + avg_out_2))
    {
        if (avg_in_1 < avg_in_2)
        {
            tmp = avg_in_1;
            avg_in_1 = avg_in_2;
            avg_in_2 = tmp;
        }
        printf("Estimated time IN for FIRST queue = %.2lf\n", avg_in_1 * count_in_1);
        printf("Real time IN for FIRST queue = %.2lf\n", time_arrival_1);
        printf("Margin of error: %.2lf %%\n", (fabs(avg_in_1 * count_in_1 - time_arrival_1) / (avg_in_1 * count_in_1) * 100));
        printf("Estimated time IN for SECOND queue = %.2lf\n", (avg_in_1 * count_in_1));
        printf("Real time IN for SECOND queue = %.2lf\n", time_arrival_2);
        printf("Margin of error: %.2lf %%\n", (fabs((avg_in_1 * count_in_1) - time_arrival_2) / ((avg_in_1 * count_in_1)) * 100));
        printf("Offtime: %.2lf\n", offtime);
    }
    else
    {
        double est = avg_out_1 * count_out_1 + avg_out_2 * count_out_2;
        printf("Estimated time processing = %.2lf\n", est);
        printf("Real time processing = %.2lf\n", total_time_processing_1 + total_time_processing_2);
        printf("Margin of error: %.2lf %%\n", (fabs(est - (total_time_processing_1 + total_time_processing_2)) / (est) * 100));
        printf("Offtime: %.2lf\n", offtime);
    }
    printf("Number of IN elemnets of FIRST queue: %d\n", count_in_1);
    printf("Number of IN elemnets of SECOND queue: %d\n", count_in_2);
    printf("Number of OUT elemnets of FIRST queue: %d\n", count_out_1);
    printf("Number of OUT elemnets of SECOND queue: %d\n\n", count_out_2);
    printf("\nMemory outlay for queue as an array: %d\n", (int)(sizeof(double) * MAX_PROCESSING + sizeof(queue_array_d)));
    printf("Memory outlay for queue as a list: %d\n\n", (int)sizeof(queue_list_d) + (int)sizeof(queue_list_n) * 5000);
    //printf("Total_time: %.4lf\n", total_time);

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
    unsigned long long t1, t2, t3, t4;

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
    }


    t1 = tick();
    rc = computing(time_q1, time_q2);
    t2 = tick();
    if (rc != OK)
        printf("\nrc = %d\n", rc);
    else
    {
        t3 = tick();
        rc = computing_list(time_q1, time_q2);
        t4 = tick();
        if (rc != OK)
            printf("\nrc = %d\n", rc);
        else
        {
            printf("Time outlay for queue as an array: %lu\n", (unsigned long int)((t2 - t1)));
            printf("Time outlay for queue as a list: %lu\n\n", (unsigned long int)((t4 - t3)));
        }
    }

    queue_array_d *queue_arr = NULL;
    int i;
    double pop_value;
    rc = create_queue_arr(&queue_arr, 10);
    if (rc == OK)
    {
        t1 = tick();
        for (i = 0; i < 10 && rc == OK; i++)
        {
            rc = push_arr(queue_arr, i);
        }
        for (int j = 0; j < 10 && rc == OK; j++)
        {
            rc = pop_arr(queue_arr, &pop_value);
        }
        t2 = tick();
        free(queue_arr->data);
        free(queue_arr);
    }
    printf("Time outlay for queue as an array (push + pop): %lu\n", (unsigned long int)((t2 - t1) / 10));

    queue_list_d *queue_list = NULL;
    rc = create_queue_list(&queue_list, 10);
    if (rc == OK)
    {
        t1 = tick();
        for (i = 0; i < 10 && rc == OK; i++)
        {
            rc = push_list(queue_list, i);
        }
        for (int j = 0; j < 10 && rc == OK; j++)
        {
            rc = pop_list(queue_list, &pop_value);
        }
        t2 = tick();
        free_list(queue_list->head);
        free(queue_list);
    }
    printf("Time outlay for queue as a list (push + pop): %lu\n", (unsigned long int)((t2 - t1) / 10));

    return OK;
}
