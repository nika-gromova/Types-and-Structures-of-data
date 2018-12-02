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

int read_2double(char *str, int n, double *value1, double *value2)
{
    int count = read_line(str, n);
    if (count <= 0)
        return INCORRECT_INPUT;
    if (strchr(str, ' ') == NULL)
        return INCORRECT_INPUT;
    char *nstr = strtok(str, " ");
    if (nstr == NULL)
        return INCORRECT_INPUT;
    char *end= NULL;
    double num[2];
    int i;
    for (i = 0; i < 2; i++)
    {
        num[i] = strtod(nstr, &end);
        if (*end != '\0')
            return INCORRECT_INPUT;
        if (nstr)
            nstr = strtok(NULL, " ");
        else
            return INCORRECT_INPUT;
    }
    if (nstr)
        return INCORRECT_INPUT;
    *value1 = num[0];
    *value2 = num[1];
    return OK;
}
