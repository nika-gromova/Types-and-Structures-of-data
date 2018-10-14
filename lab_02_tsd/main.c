#include "io.h"
#include "defines.h"
#include "structure.h"
#include "operations.h"
#include "sorting.h"
#include "time.h"

#define TABLE 45

void info(void)
{
    printf("\nThe format of output information:\n"
           "model of the car,\n"
           "country of manufacture,\n"
           "price of the car,\n"
           "color of the car,\n"
           "total mileage,\n"
           "count of previous repairs,\n"
           "count of previous owners,\n"
           "condition(year of manufacture or period of guarantee in years\n\n"
           "Sorting field is price.\n\n");
    printf("\n----------MENU----------\n");
    printf("1. Add a line to a table (maximum 5 additions)\n"
           "2. Delete a line from the table\n"
           "3. Search for not new cars of input model and in input range of prices that had no repairs and only one previous owner\n"
           "4. Printing sorted table of keys and unsorted initial table\n"
           "5. Printing sorted initial table\n"
           "6. Printing ordered initial table using sorted table of keys\n"
           "7. Printing time measurements (in ticks) for sorting table of keys VS sorting initial table\n"
           "8. Printing time measurements (in ticks) for different types of sorting\n"
           "9. Printing table in file.\n\n");
}

int main(void)
{
    char *file_name = "data.txt";
    int rc = OK;
    struct car table[TABLE];
    int n;

    for (int i = 0; i < TABLE; i++)
    {
        table[i].model[0] = '\0';
        table[i].country[0] = '\0';
        table[i].color[0] = '\0';
        table[i].price = 0;
        table[i].mileage = 0;
        table[i].owners = 0;
        table[i].repairs = 0;
        table[i].condition = 0;
        table[i].years.new = 0.0;
    }
    struct car *p_table[TABLE];
    for (int i = 0; i < TABLE; i++)
        p_table[i] = &(table[i]);

    n = 40;
    int choice = 0;
    int cont = 1;
    char input[5];
    printf("Hello! This is a program simulating a database work.\n"
           "Table consist of several fields and contains information about available cars int the shop.\n"
           "Sorting field is price.\n");
    while (cont)
    {
        info();
        rc = read_data(file_name, p_table, n);
        if (rc == OK)
        {
            struct key keys[TABLE];
            for (int i = 0; i < TABLE; i++)
            {
                keys[i].index = i;
                keys[i].value = p_table[i]->price;
            }
            struct key *p_keys[TABLE];
            for (int i = 0; i < TABLE; i++)
                p_keys[i] = &(keys[i]);
            while (choice < 1 || choice > 9)
            {
                printf("Print 1 - 9:\n");
                int k = read_line(input, 5);
                printf("\n%d\n", k);
                if ( k > 0)
                    choice = atoi(input);
                else
                    choice = 0;
            }

            if (choice == 1)
            {
                if (n < 45)
                {
                    struct car tmp = {"\0", "\0", "\0", 0};
                    struct car *p_tmp = &tmp;
                    rc = input_car(p_tmp);
                    if (rc == OK)
                    {
                        table[n] = tmp;
                        p_table[n] = &(table[n]);
                        add(file_name, tmp);
                        n++;
                        print_data(p_table, n);
                    }
                }
                else
                {
                    printf("The storage is full.");
                    rc = OVERFLOW;
                }
            }
            if (choice == 2)
            {
                if (n > 0)
                {
                    int del;
                    printf("Input index to delete (0 - %d):\n", n - 1);
                    if (scanf("%d", &del) == 1 && del > -1 && del < n)
                    {
                        n--;
                        for (int i = del; i < n ; i++)
                        {
                            p_table[i] = p_table[i + 1];
                        }
                        print_data(p_table, n);
                        rc = save_data(file_name, p_table, n);
                    }
                    else
                    {
                        for (char ch = getchar(); ch != '\n'; ch = getchar())
                            ;
                        printf("Incorrect input");
                        rc = INPUT_ERROR;
                    }
                }
                else
                {
                    printf("The storage is empty. Nothing to delete.");
                    rc = EMPTY;
                }
            }
            if (choice == 3)
            {
                printf("\nInput model for search:\n");
                char ch[15];
                int low, high;
                int in = 0;
                if (read_line(ch, 16) > 0)
                {
                    printf("\nInput low and high bounds of price for search (format:a b):\n");
                    if (scanf("%d %d", &low, &high) == 2 && (low >= 0) && (high >= 0) && (low < high))
                    {
                        printf("%-15s%-20s%-15s%10s%15s%10s%10s%15s\n", "model:", "country:", "price:", "color:", "mileage:", "repairs:", "owners:", "condition:");
                        print_sep(110);
                        for (int i = 0; i < n; i++)
                        {
                            if (strcmp(table[i].model, ch) == 0)
                            {
                                if (table[i].price >= low && table[i].price <= high)
                                {
                                    if (table[i].condition == 2 && table[i].owners == 1 && table[i].repairs == 0)
                                    {
                                        print_car(table[i]);
                                        in = 1;
                                    }
                                }
                            }
                        }
                        if (in == 0)
                            printf("There are no such cars in the shop");
                    }
                    else
                    {
                        for (char ch = getchar(); ch != '\n'; ch = getchar())
                            ;
                        printf("Incorrect input\n");
                    }
                }
                else
                    printf("Incorrect input\n");
            }
            if (choice == 4)
            {
                printf("Sorted table of keys:\n");
                sort_keys_bubble(n, p_keys);
                print_keys(p_keys, n);
                printf("\n\n\n");
                printf("Unsorted initial table\n");
                print_data(p_table, n);
            }
            if (choice == 5)
            {
                printf("Sorted initial table:\n");
                sort_table_bubble(n, p_table);
                print_data(p_table, n);
            }
            if (choice == 6)
            {
                printf("Sorted table of keys and matching initial table:\n");
                sort_keys_bubble(n, p_keys);
                printf("\n\n");
                print_table_with_keys(p_keys, p_table, n);
            }
            if (choice == 7)
            {
                printf("Time measurements while sorting initial table VS while sorting table of keys\n");
                {
                    unsigned long long t1, t2, time;
                    rc = read_data(file_name, p_table, n);
                    if (rc == OK)
                    {
                        t1 = tick();
                        for (int i = 0; i < 10; i++)
                            sort_table_bubble_2(n, table);
                        t2= tick();
                        time = ((t2 - t1) / 10);
                        printf("\nTime for sorting the whole table: %I64u\n", time);
                    }
                }

                {
                    unsigned long long t1, t2, time;
                    rc = read_data(file_name, p_table, n);
                    if (rc == OK)
                    {
                        t1 = tick();
                        for (int i = 0; i < 10; i++)
                            sort_keys_bubble_2(n, keys);
                        t2= tick();
                        time = ((t2 - t1) / 10);
                        printf("\nTime for sorting the keys table:  %I64u\n", time);
                    }
                }
            }
            if (choice == 8)
            {
                printf("Time measurements while sorting table of keys (buble sort and cocktail sort) VS while sorting initial table (buble sort and cocktail sort)\n");
                {
                    unsigned long long t1, t2, time;
                    rc = read_data(file_name, p_table, n);
                    if (rc == OK)
                    {
                        for (int i = 0; i < n; i++)
                        {
                            keys[i].index = i;
                            keys[i].value = table[i].price;
                        }
                        t1 = tick();
                        for (int i = 0; i < 10; i++)
                            sort_keys_bubble_2(n, keys);
                        t2= tick();
                        time = ((t2 - t1) / 10);
                        printf("\nTime for sorting the keys table with bubble sort:    %I64u\n", time);
                    }
                }

                {
                    unsigned long long t1, t2, time;
                    rc = read_data(file_name, p_table, n);
                    if (rc == OK)
                    {
                        for (int i = 0; i < n; i++)
                        {
                            keys[i].index = i;
                            keys[i].value = table[i].price;
                        }
                        t1 = tick();
                        for (int i = 0; i < 10; i++)
                            sort_keys_cocktail_2(n, keys);
                        t2= tick();
                        time = (t2 - t1) / 10;
                        printf("\nTime for sorting the keys table with cocktail sort:  %I64u\n\n", time);
                    }
                }

                {
                    unsigned long long t1, t2, time;
                    rc = read_data(file_name, p_table, n);
                    if (rc == OK)
                    {
                        t1 = tick();
                        for (int i = 0; i < 10; i++)
                            sort_table_bubble_2(n , table);
                        t2= tick();
                        time = (t2 - t1) / 10;
                        printf("\nTime for sorting the whole table with bubble sort:   %I64u\n\n", time);
                    }
                }

                {
                    unsigned long long t1, t2, time;
                    rc = read_data(file_name, p_table, n);
                    if (rc == OK)
                    {
                        t1 = tick();
                        for (int i = 0; i < 10; i++)
                            sort_table_cocktail(n, table);
                        t2= tick();
                        time = (t2 - t1) / 10;
                        printf("\nTime for sorting the whole table with cocktail sort: %I64u\n\n", time);
                    }
                }

            }
            if (choice == 9)
                print_data(p_table, n);
        }
        else
            printf("!!! Error in reading file %s !!!\n", file_name);
        printf("\nDo you want to continue work? (1 - yes/ 0 - no):\n");

        if (scanf("%d", &cont) != 1 || cont != 1)
        {
            rc = OK;
            cont = 0;
        }
        choice = 0;
    }

    return rc;
}
