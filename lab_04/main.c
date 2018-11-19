#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defines.h"
#include "io.h"
#include "my_types.h"
#include "array_st.h"
#include "list_st.h"

void info_menu(void)
{
    printf("If you want to push element, please enter 1.\n");
    printf("If you want to pop element, please enter 2.\n");
    printf("If you want to see all decreasing sets of numbers in stack in reversed order, please enter 3.\n");
    printf("If you want to look through the whole stack, please enter 4.\n");
    printf("If you want to look through the list of memory addresses of elements in stack, please enter 5.\n");
    printf("If you want to look through the list of memory addresses of freed addresses, please enter 6.\n");
    printf("If you want to exit, please enter 7.\n\n");
}

unsigned long long tick(void)
{
    unsigned long d;
    __asm__ __volatile__ ("rdtsc" : "=A"(d));
    return d;
}

int main(void)
{
    printf("Hello! This is a programme of simulating work of stack. Stack can only have integer numbers!\n"
           "You can push and pop elemnts, look thrugh the whole stack without deletion.\n\n");
    int limit = 0;
    int choice = 0;
    char buf[20];
    int count_symb_in_input_line;
    unsigned long long t1, t2, t3, t4, time_array = 0, time_list = 0;
    int push_value;
    int *pop_value;
    int rc = OK;

    array_stack_t *stack_array = NULL;
    t1 = tick();
    stack_array = create_stack_arr();
    if (stack_array == NULL)
        return MEMORY_ERROR;
    t2 = tick();
    time_array += (t2 - t1);

    list_stack_node *stack_list = NULL;
    list_stack_node *pop_node = NULL;
    list_stack_node *push_node = NULL;
    int size_stack_list = 0;

    list_stack_node *free_adderesses[100];
    list_stack_node *occupied_addresses[100];
    int iter_free_addresses = 0, iter_occupied_addresses = 0;

    while (limit <= 0)
    {
        printf("Please enter the size of stack (integer positive number and not null):\n");
        count_symb_in_input_line = read_int(buf, sizeof(buf), &limit);
        if (count_symb_in_input_line != OK)
        {
            printf("Incorrect input.\n");
            limit = 0;
        }
    }

    while (1)
    {
        while (choice < 1 || choice > 7)
        {
            info_menu();
            printf("Choose 1 - 6:\n");
            count_symb_in_input_line = read_line(buf, sizeof(buf));
            if (count_symb_in_input_line == 0)
            {
                printf("Incorrect input.\n\n");
                choice = 0;
            }
            else
                choice = atoi(buf);
        }
        if (choice == 1)
        {
            if (stack_array->top >= limit && size_stack_list >= limit)
            {
                printf("Stack overflow! Please pop some elements first.\n\n");
                choice = STACK_OVERFLOW;
            }
            else
            {
                printf("Please, enter an integer number:\n");
                rc = read_int(buf, sizeof(buf), &push_value);
                if (rc == OK)
                {
                    t1 = tick();
                    stack_array = push_arr(stack_array, push_value);
                    if (stack_array == NULL)
                    {
                        printf("Some memory errors :(\n\n");
                        return MEMORY_ERROR;
                    }
                    else
                    {
                        printf("Element %d was pushed to stack_array!\n\n", push_value);

                    }
                    t2 = tick();
                    time_array += (t2 - t1);

                    t1 = tick();
                    push_node = push_list(&stack_list, push_value);
                    if (push_node == NULL)
                    {
                        return MEMORY_ERROR;
                    }
                    else
                    {
                        t3 = tick();
                        for (int i = 0; i < iter_free_addresses; i++)
                        {
                            if (free_adderesses[i] == push_node)
                            {
                                memmove(free_adderesses + i, free_adderesses + i + 1, sizeof(int) * (iter_free_addresses - i - 1));
                                iter_free_addresses--;
                                break;
                            }
                        }
                        occupied_addresses[iter_occupied_addresses] = push_node;
                        iter_occupied_addresses++;
                        t4 = tick();
                        printf("Element %d was pushed to stack_list!\n\n", push_value);
                        size_stack_list++;
                    }
                    t2 = tick();
                    time_list += (t2 - t1);
                    time_list -= (t4 - t3);
                    choice = 0;
                }
                else
                {
                    printf("Incorrect input! You should enter only one integer number and press 'enter' :)\n");
                    choice = 1;
                }
            }
        }
        if (choice == 2)
        {
            t1 = tick();
            pop_value = pop_arr(stack_array);
            if (pop_value != NULL)
            {
                printf("Element %d was popped from stack_array.\n", *pop_value);
            }
            t2 = tick();
            time_array += (t2 - t1);

            t1 = tick();
            pop_node = pop_list(&stack_list);
            if (pop_node != NULL)
            {
                t3 = tick();
                occupied_addresses[iter_occupied_addresses] = NULL;
                iter_occupied_addresses--;
                free_adderesses[iter_free_addresses] = pop_node;
                iter_free_addresses++;
                t4 = tick();
                printf("Element %d was popped from list_array.\n\n", pop_node->data);
                size_stack_list--;
                free(pop_node);
            }
            t2 = tick();
            time_list += (t2 - t1);
            time_list -= (t4 - t3);
            choice = 0;
        }
        if (choice == 3)
        {
            t1 = tick();
            task_arr(stack_array);
            t2 = tick();
            time_array += (t2 - t1);

            t1 = tick();
            task_list(stack_list);
            t2 = tick();
            time_list += (t2 - t1);

            choice = 0;
        }
        if (choice == 4)
        {
            t1 = tick();
            print_stack_arr(stack_array);
            t2 = tick();
            time_array += (t2 - t1);

            t1 = tick();
            print_stack_list(stack_list);
            t2 = tick();
            time_list += (t2 - t1);
            choice = 0;
        }
        if (choice == 5)
        {
            if (iter_occupied_addresses <= 0)
                printf("All memory is free.\n\n");
            else
            {
                for (int i = 0; i < iter_occupied_addresses; i++)
                    printf("%p ", occupied_addresses[i]);
                printf("\n\n");
            }
            choice = 0;
        }
        if (choice == 6)
        {
            if (iter_free_addresses <= 0 && iter_free_addresses > 0)
                printf("All memory is occupied.\n\n");
            else if (iter_free_addresses <= 0 && iter_free_addresses <= 0)
                printf("All memory is free.\n\n");
            else
            {
                for (int i = 0; i < iter_free_addresses; i++)
                    printf("%p ", free_adderesses[i]);
                printf("\n\n");
            }
            choice = 0;
        }
        if (choice == 7)
        {
            printf("Time spent for processing stack as an array (in ticks): (I64u) %u\n", (unsigned int) time_array);
            printf("Memory outlay for stack as an array (in bytes): %u\n\n", (unsigned int) (sizeof(array_stack_t) + sizeof(int) * stack_array->top));
            printf("Time spent for processing stack as a list (in ticks): (I64u) %u\n", (unsigned int) time_list);
            printf("Memory outlay for stack as a list (in bytes): %u\n", (unsigned int) (sizeof(list_stack_node) * size_stack_list));
            free_stack_arr(stack_array);
            delete_stack_list(stack_list);
            return OK;
        }
    }

    return OK;
}
