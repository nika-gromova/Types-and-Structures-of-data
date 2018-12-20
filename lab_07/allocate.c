#include <stdlib.h>
#include "allocate.h"

int **allocate_matrix(int n, int m)
{
    int **matrix = calloc(n, sizeof(int *));
    if (matrix)
    {
        for (int i = 0; i < n; i++)
        {
            matrix[i] = calloc(m, sizeof(int));
            if (!matrix[i])
            {
                free_matrix(matrix, n);
                return NULL;
            }
        }
    }
    return matrix;
}

void free_matrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}
