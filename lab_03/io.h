#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int read_row(const char *file_name, double **row, int *n, int *not_null);
int read_matrix(const char *file_name, double ***matrix, int *n, int *m, int *not_null);
int input_byhand(double ***matrix, int *n, int *m, double **row, int *row_size, int *not_null_a, int *not_null_b);
void print_matrix(double **matrix, int n, int m);

#endif // IO_H
