#ifndef PROCESS_H
#define PROCESS_H

#include <math.h>
#include <stdlib.h>
#include <assert.h>

int partioning(double **matrix, double **A, int **IA, int **JA, int not_null_a, int n, int m);
int partioning_vector(double *row_vector, double **B, int **IB, int row_size, int not_null);
int multiplication(double *A, int *IA, int *JA, int m, int column_n, double *B, int *IB, int not_null_b, double *res, int *not_null_res);
int mult_vector_matrix(double **matrix_1, int n_1, int m_1, double *vector, int m_2, double *result);

#endif // PROCESS_H
