#ifndef IO_H
#define IO_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

int check_sign(char **p_elem, int *sign);
int input(char *my_str, int M[], int *n, int *P, int *sign_m, int *sign_p, int *i_point);
void output(const int res[], int n, int P, int sign_m, int sign_p, int i_point);

#endif // IO_H
