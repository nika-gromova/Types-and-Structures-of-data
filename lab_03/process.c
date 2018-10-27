#include "process.h"
#include "defines.h"


int partioning(double **matrix, double **A, int **IA, int **JA, int not_null_a, int n, int m)
{
    double *tmp_A = malloc(not_null_a * sizeof(double));
    if (!tmp_A)
        return MEMORY_ERROR;
    int *tmp_IA = malloc(not_null_a * sizeof(int));
    if (!tmp_IA)
        return MEMORY_ERROR;
    int *tmp_JA = malloc((m + 1) * sizeof(int));
    if (!tmp_JA)
        return MEMORY_ERROR;
    int tmp_col = 0, k = 0, h = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fabs(matrix[j][i]) > EPS)
            {
                tmp_A[k] = matrix[j][i];
                tmp_IA[k] = j;
                if (tmp_col == 0)
                {
                    tmp_JA[h] = k;
                    h++;
                    tmp_col = 1;
                }
                k++;
            }
        }
        if (tmp_col == 0)
        {
            tmp_JA[h] = k;
            h++;
        }
        tmp_col = 0;
    }
    tmp_JA[h] = k;
    *A = tmp_A;
    *IA = tmp_IA;
    *JA = tmp_JA;
    return OK;
}

int partioning_vector(double *row_vector, double **B, int **IB, int row_size, int not_null)
{
    double *tmp_B = malloc(not_null * sizeof(double));
    if (!tmp_B)
        return MEMORY_ERROR;
    int *tmp_IB = malloc(not_null * sizeof(int));
    if (!tmp_IB)
        return MEMORY_ERROR;
    int k = 0;
    for (int i = 0; i < row_size; i++)
    {
        if (fabs(row_vector[i]) > EPS)
        {
            tmp_B[k] = row_vector[i];
            tmp_IB[k] = i;
            k++;
        }
    }
    *B = tmp_B;
    *IB = tmp_IB;
    return OK;
}

int multiplication(double *A, int *IA, int *JA, int m, int column_n, double *B, int *IB, int not_null_b, double *res, int *not_null_res)
{
    assert(m >= not_null_b);
    int *IP = malloc(m * sizeof(int));
    if (!IP)
        return MEMORY_ERROR;
    for (int i = 0; i < m; i++)
        IP[i] = -1;
    for (int i = 0; i < not_null_b; i++)
        IP[IB[i]] = i;
    double mult = 0.0;
    int k = 0;
    *not_null_res = 0;
    for (int i = 0; i < column_n; i++)
    {
        for (int j = JA[i]; j < JA[i + 1]; j++)
        {
            if (IP[IA[j]] != -1)
                mult += A[j] * B[IP[IA[j]]];
        }
        if (mult != 0)
            (*not_null_res)++;
        res[k] = mult;
        mult = 0;
        k++;
    }
    free(IP);
    return OK;
}

int mult_vector_matrix(double **matrix_1, int n_1, int m_1, double *vector, int m_2, double *result)
{
    if (n_1 < 1 || m_1 < 1 || m_2 < 1)
        return N_M_PARAMS_ERROR;
    if (n_1 != m_2)
        return N_M_PARAMS_ERROR;
    for (int i = 0; i < m_1; i++)
    {
        result[i] = 0;
        for (int j = 0; j < n_1; j++)
            result[i] += matrix_1[j][i] * vector[j];
    }
    return OK;
}

