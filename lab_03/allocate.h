#ifndef ALLOCATE_H
#define ALLOCATE_H

#include <stdlib.h>

double **allocate_matrix(int n, int m);
void free_matrix(double **matrix, int n);

#endif // ALLOCATE_H
