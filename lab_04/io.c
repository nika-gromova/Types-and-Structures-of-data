#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "io.h"
#include "defines.h"

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
    else
        return i;
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

int read_int(char *str, int n, int *value)
{
    int count = read_line(str, n);
    if (count <= 0)
        return INCORRECT_INPUT;
    char *end= NULL;
    int num = strtol(str, &end, 10);
    if (*end != '\0')
        return INCORRECT_INPUT;
    if (num == 0 && count == 1)
    {
        if (strcmp(str, "0") == 0)
        {
            *value = 0;
            return OK;
        }
    }
    else if (num != 0)
    {
        *value = num;
        return OK;
    }
    return INCORRECT_INPUT;
}

void print_sep(int n)
{
    for (int i = 0; i < n; i++)
        printf("-");
    printf("\n");
}
