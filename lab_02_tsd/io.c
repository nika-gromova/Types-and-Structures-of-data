#include "io.h"
#include "defines.h"
#include "structure.h"

int input_str(char *str, struct car *table_element)
{
    char *sep = "|";
    char *istr = '\0';
    unsigned int num;
    float condition;
    istr = strtok(str, sep);
    if (istr)
        for (int i = 0; i < strlen(istr) + 1; i++)
            table_element->model[i] = istr[i];
    else
        return READ_ERROR;

    istr = strtok(NULL, sep);
    if (istr)
        for (int i = 0; i < strlen(istr) + 1; i++)
            table_element->country[i] = istr[i];
    else
        return READ_ERROR;

    istr = strtok(NULL, sep);
    if (istr)
    {
        num = atoi(istr);
        if (strlen(istr) != 1 && num == 0)
            return READ_ERROR;
        table_element->price = num;
    }
    else
        return READ_ERROR;

    istr = strtok(NULL, sep);
    if (istr)
        for (int i = 0; i < strlen(istr) + 1; i++)
            table_element->color[i] = istr[i];
    else
        return READ_ERROR;

    istr = strtok(NULL, sep);
    if (istr)
    {
        num = atoi(istr);
        if (strlen(istr) != 1 && num == 0)
            return READ_ERROR;
        table_element->mileage = num;
    }
    else
        return READ_ERROR;

    istr = strtok(NULL, sep);
    if (istr)
    {
        num = atoi(istr);
        if (strlen(istr) != 1 && num == 0)
            return READ_ERROR;
        table_element->repairs = num;
    }
    else
        return READ_ERROR;

    istr = strtok(NULL, sep);
    if (istr)
    {
        num = atoi(istr);
        if (strlen(istr) != 1 && num == 0)
            return READ_ERROR;
        table_element->owners = num;
    }
    else
        return READ_ERROR;

    istr = strtok(NULL, sep);
    if (istr)
    {
        condition = atof(istr);
        if (strlen(istr) != 1 && condition == 0)
            return READ_ERROR;
        if (condition > 1000)
        {
            table_element->condition = 2;
            table_element->years.old = (int) condition;
        }
        else
        {
            table_element->condition = 1;
            table_element->years.new = condition;
        }
    }
    else
        return READ_ERROR;
    return OK;
}

int read_data(char *file_name, struct car **table, int n)
{
    int rc = OK;
    char str[200];
    char ch;
    FILE *f;
    f = fopen(file_name, "r");
    if (f)
    {
        for (int i = 0; i < n; i++)
        {
            if (fgets(str, 200, f) != NULL)
            {
                if (str[strlen(str) - 1] != '\n')
                {
                    rc = READ_ERROR;
                    break;
                }
                rc = input_str(str, table[i]);
            }
            else
            {
                rc = READ_ERROR;
                break;
            }
        }
        if (fscanf(f, "%c", &ch) != '\n' && feof(f) == 0)
            return READ_ERROR;
        fclose(f);
    }
    else
    {
        printf("Can't open a file.\n");
        rc = OPEN_FILE_ERROR;
    }
    return rc;
}

void print_sep(int n)
{
    for (int i = 0; i < n; i++)
        printf("-");
    printf("\n");
}

int read_line(char *str, int n)
{
    char ch;
    int i = 0;
    int flag_overflow = 0;
    if ((ch = getchar()) != '\n')
    {
        str[i] = ch;
        i++;
    }
    while((ch = getchar()) != '\n' && ch != EOF)
    {
        if (i < n - 1)
            str[i++] = ch;
        else
            flag_overflow = 1;
    }
    if (flag_overflow == 0)
        str[i] = '\0';
    else
        i = 0;
    return i;
}

int input_car(struct car *cur)
{
    char ch1[16], ch2[16], ch3[16];
    unsigned int tmp;
    double num;
    int s;
    printf("Input model (1 to 15 symbols):\n");
    print_sep(15);
    if ((s = read_line(ch1, 16)) > 0)
    {
        for (int i = 0; i < strlen(ch1); i++)
            cur->model[i] = ch1[i];
        printf("Input country (1 to 15 symbols):\n");
        print_sep(15);
        if((s = read_line(ch2, 16)) > 0)
        {
            for (int i = 0; i < strlen(ch2) + 1; i++)
                cur->country[i] = ch2[i];
            printf("Input color (1 to 15 symbols):\n");
            print_sep(15);
            if ((s = read_line(ch3, 16)) > 0)
            {
                for (int i = 0; i < strlen(ch3) + 1; i++)
                    cur->color[i] = ch3[i];
                if (strlen(ch3) <= 15)
                printf("\nInput price:\n");
                if (scanf("%u", &tmp) == 1 && tmp >= 0)
                {
                    cur->price = tmp;
                    printf("\nInput mileage:\n");
                    if (scanf("%u", &tmp) == 1 && tmp >= 0)
                    {
                        cur->mileage = tmp;
                        printf("\nInput number of previous repairs:\n");
                        if (scanf("%u", &tmp ) == 1 && tmp >= 0)
                        {
                            cur->repairs = tmp;
                            printf("\nInput number of previous owners:\n");
                            if (scanf("%u", &tmp) == 1 && tmp >= 0)
                            {
                                cur->owners = tmp;
                                printf("\nInput manufacture year or guaranty period (in years):\n");
                                if (scanf("%lf", &num) == 1 && tmp >= 0)
                                {
                                    if (num > 1000)
                                    {
                                        cur->condition = 2;
                                        cur->years.old = (int) num;
                                    }
                                    else
                                    {
                                        cur->condition = 1;
                                        cur->years.new = num;
                                    }
                                    return OK;
                                }
                                else
                                    goto error;
                            }
                            else
                                goto error;
                        }
                        else
                            goto error;
                    }
                    else
                        goto error;
                }
                else
                    goto error;
            }
            else
                goto error;
        }
        else
            goto error;
    }
    else
        goto error;
    error:
    {
        for (char ch = getchar(); ch != '\n'; ch = getchar())
            ;
        printf("Incorrect input\n");
        return INPUT_ERROR;
    }
}

void print_data(struct car **table, int n)
{
    printf("\n%-8s%-15s%-20s%-15s%10s%15s%10s%10s%15s\n", "index:", "model:", "country:", "price:", "color:", "mileage:", "repairs:", "owners:", "condition:");
    print_sep(118);
    for (int i = 0; i < n; i++)
    {
        printf("%-8d%-15s%-20s%-15u%10s%15u%10u%10u", i, table[i]->model, table[i]->country, table[i]->price, table[i]->color,\
               table[i]->mileage, table[i]->repairs, table[i]->owners);
        if (table[i]->condition == 1)
            printf("%15.1f\n", table[i]->years.new);
        else
            printf("%15d\n", table[i]->years.old);
    }
}

void print_keys(struct key **table, int n)
{
    printf("\n%-10s%10s\n", "index:", "value:");
    for (int i = 0; i < n; i++)
        printf("%-10d%10u\n", table[i]->index, table[i]->value);
}

void print_table_with_keys(struct key **keys, struct car **table, int n)
{
    int tmp_i;
    printf("\n%-8s%-15s%-20s%-15s%10s%15s%10s%10s%15s\n", "index:", "model:", "country:", "price:", "color:", "mileage:", "repairs:", "owners:", "condition:");
    print_sep(118);
    for (int i = 0; i < n; i++)
    {
        tmp_i = keys[i]->index;
        printf("%-8d%-15s%-20s%-15u%10s%15u%10u%10u", i, table[tmp_i]->model, table[tmp_i]->country, table[tmp_i]->price, table[tmp_i]->color,\
               table[tmp_i]->mileage, table[tmp_i]->repairs, table[tmp_i]->owners);
        if (table[tmp_i]->condition == 1)
            printf("%15.1f\n", table[tmp_i]->years.new);
        else
            printf("%15d\n", table[tmp_i]->years.old);
    }
}

void print_car(struct car elem)
{
    printf("%-15s%-20s%-15u%10s%15u%10u%10u", elem.model, elem.country, elem.price, elem.color,\
           elem.mileage, elem.repairs, elem.owners);
    if (elem.condition == 1)
        printf("%15.1f\n", elem.years.new);
    else
        printf("%15d\n", elem.years.old);
}

int save_data(char *filename, struct car **table, int n)
{
    FILE *f = fopen(filename, "w");
    if (f)
    {
        for (int i = 0; i < n; i++)
        {
            fprintf(f, "%s|%s|%u|%s|%u|%u|%u|", table[i]->model, table[i]->country, table[i]->price, table[i]->color,\
                   table[i]->mileage, table[i]->repairs, table[i]->owners);
            if (table[i]->condition == 1)
                fprintf(f, "%.1f\n", table[i]->years.new);
            else
                fprintf(f, "%d\n", table[i]->years.old);
        }
        fclose(f);
    }
    else
        return OPEN_FILE_ERROR;
    return OK;
}
