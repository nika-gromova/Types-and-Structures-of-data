#include "allocate.h"

/**
 * @brief allocate_matrix Функция выделения памяти под матрицу с хранением указателей на каждую строку матрицы
 * @param n - количество строк матрицы
 * @param m - количество столбцов матрицы
 * @return возвращает NULL, если память выделить не удалось, либо указатель на массив указателей на строки матрицы
 */
double **allocate_matrix(int n, int m)
{
    double **matrix = malloc((n + 1) * sizeof(double *));
    if (matrix)
    {
        double *data = calloc(n * m, sizeof(double));
        if (data)
        {
            for (int k = 0; k < n; k++)
                matrix[k] = data + k * m;
            matrix[n] = data;
        }
        else
        {
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

/**
 * @brief free_matrix Функция освобождения памяти из-под матрицы
 * @param matrix - указатель на массив указателей на строки матрицы
 * @param n - размер массива
 */
void free_matrix(double **matrix, int n)
{
    free(matrix[n]);
    free(matrix);
}
