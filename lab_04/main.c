#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "io.h"
#include "my_types.h"
#include "array_st.h"
#include "list_st.h"

void info_menu(void)
{
    printf("Press 1 - if you want to push element.\n");
    printf("Press 2 - if you want to pop element.\n");
    printf("Press 3 - if you want to see all decreasing sets of numbers in stack in reversed order.\n");
    printf("Press 4 - if you want to look through the whole stack.\n");
    printf("Press 5 - if you want to look through the list of occupied and freed memory addresses.\n");
    printf("Press 6 - if you want to see time and memory outlays.\n");
    printf("Press 7 - if you want to exit.\n\n");
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
    int pop_value;
    int rc = OK;

    array_stack_t *stack_array = NULL;

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

    t1 = tick();
    stack_array = create_stack_arr(limit);
    if (stack_array == NULL)
        return MEMORY_ERROR;
    t2 = tick();
    time_array += (t2 - t1);

    while (1)
    {
        while (choice < 1 || choice > 7)
        {
            info_menu();
            printf("Choose 1 - 6:\n");
            count_symb_in_input_line = read_int(buf, sizeof(buf), &choice);
            if (count_symb_in_input_line != OK || choice < 1 || choice > 7)
            {
                printf("Incorrect input.\n\n");
                choice = 0;
            }
        }
        if (choice == 1)
        {
            if (size_stack_list >= limit && stack_array->top >= limit)
            {
                printf("\nStack overflow! Please pop some elements first.\n\n");
                choice = 0;
            }
            else
            {
                printf("\nPlease, enter an integer number:\n");
                rc = read_int(buf, sizeof(buf), &push_value);
                if (rc == OK)
                {
                    t1 = tick();
                    stack_array = push_arr(stack_array, push_value);
                    if (stack_array == NULL)
                    {
                        printf("\nStack overflow! Please pop some elements first.\n\n");
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
                        add_remove_addresses(occupied_addresses, free_adderesses, &iter_occupied_addresses, &iter_free_addresses, push_node);
                        t4 = tick();
                        time_list -= (t4 - t3);
                        printf("Element %d was pushed to stack_list!\n\n", push_value);
                        size_stack_list++;
                    }
                    t2 = tick();
                    time_list += (t2 - t1);
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
            pop_value = pop_arr(stack_array, &rc);
            if (rc != -1)
            {
                printf("\nElement %d was popped from stack_array.\n", pop_value);
            }
            else
            {
                printf("\nStack_array is empty.\n");
            }
            t2 = tick();
            time_array += (t2 - t1);

            t1 = tick();
            pop_value = pop_list(&stack_list, &pop_node, &rc);
            if (rc != -1)
            {
                t3 = tick();
                add_remove_addresses(occupied_addresses, free_adderesses, &iter_occupied_addresses, &iter_free_addresses, pop_node);
                t4 = tick();
                time_list -= (t4 - t3);
                printf("Element %d was popped from list_array.\n", pop_value);
                printf("Memory address: %p\n\n", pop_node);
                size_stack_list--;
            }
            else
            {
                printf("\nStack_list is empty.\n\n");
            }
            t2 = tick();
            time_list += (t2 - t1);
            choice = 0;
        }
        if (choice == 3)
        {
            t1 = tick();
            task_arr(stack_array);
            t2 = tick();
            time_array += (t2 - t1);

            t1 = tick();
            task_list(&stack_list, free_adderesses, &iter_free_addresses);
            t2 = tick();
            time_list += (t2 - t1);

            iter_occupied_addresses = 0;
            size_stack_list = 0;

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
            if (iter_occupied_addresses <= 0 && iter_free_addresses <= 0)
                printf("All memory is free.\n\n");
            else
            {
                printf("\nOccupied memory:\n");
                if (iter_occupied_addresses > 0)
                {
                    for (int i = 0; i < iter_occupied_addresses; i++)
                        printf("%p ", occupied_addresses[i]);
                }
                else
                    printf("None\n");
                printf("\n\n");
                printf("Freed memory:\n");
                if (iter_free_addresses > 0)
                {
                    for (int i = 0; i < iter_free_addresses; i++)
                        printf("%p ", free_adderesses[i]);
                }
                else
                    printf("None\n");
                printf("\n\n");
            }
            choice = 0;
        }
        if (choice == 6)
        {
            printf("\nTime spent for processing stack as an array and as a list(in ticks):\n");
            print_sep(20);
            printf("%10s|%-10s\n", "array", "list");
            printf("%10lu|%-10lu\n", (unsigned long int) time_array, (unsigned long int) time_list);
            print_sep(20);
            printf("\nMemory outlay for stack as an array (in bytes): %u\n\n", (unsigned int) (sizeof(array_stack_t) + sizeof(int) * stack_array->top));
            printf("Memory outlay for stack as a list (in bytes): %u\n\n", (unsigned int) (sizeof(list_stack_node) * size_stack_list + sizeof(int)));
            choice = 0;
        }
        if (choice == 7)
        {
            free_stack_arr(stack_array);
            delete_stack_list(stack_list);
            return OK;
        }
    }
    return OK;
}
