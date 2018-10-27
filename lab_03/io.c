#include "defines.h"
#include "io.h"
#include "allocate.h"

int read_row(const char *file_name, double **row, int *n, int *not_null)
{
    FILE *f;
    int rc = OK;
    int i = 0;
    double *buf = NULL;
    f = fopen(file_name, "r");
    if (f)
    {
        if (fscanf(f, "%d %d", n, not_null) == 2)
        {
            if (*n > 0 && *not_null > 0 && *not_null <= (*n))
            {
                buf = calloc((*n), sizeof(double));
                if (buf)
                {
                    for (int k = 0; k < *not_null && rc == OK; k++)
                    {
                        if (fscanf(f, "%d", &i) == 1 && i >= 0 && i < *n)
                        {
                            if ((buf[i] != 0) || fscanf(f, "%lf", &buf[i]) != 1 || buf[i] == 0)
                                rc = INPUT_ERROR;
                        }
                        else
                            rc = INPUT_ERROR;
                        if (k + 1 != *not_null && feof(f) != 0)
                            rc = INPUT_ERROR;
                    }
                    if (rc == INPUT_ERROR)
                        free(buf);
                    else
                        *row = buf;
                }
                else
                    rc = MEMORY_ERROR;
            }
            else
                rc = N_M_PARAMS_ERROR;
        }
        else
            rc = INPUT_ERROR;
        fclose(f);
    }
    else
        return FILE_OPEN_ERROR;
    return rc;
}

/**
 * Функция считывает матрицу, записанной в файле "file_name" в координатном виде, и записывает её в выделенный блок памяти, указатель на которую изменяется в самой функции.
 * @brief read_matrix
 * @param file_name [in] - имя файла, откуда считывается матрица
 * @param matrix [in] - указатель на массив указателей на строки матрицы
 * @param n [in] - указатель на переменную, содержащую количество строк матрицы
 * @param m [in] - указатель на переменную, содержащую количество столбцов матрицы
 * @return rc - возвращает INPUT_ERROR, если не удалось считать числа или текущий считанный элемент матрицы равен нулю или элемент матрицы с текущими считанными индексаи уже был введен,
 либо MEMORY_ERROR, если не удалось выделить память для считываемой матрицы,
 либо N_M_ERROR, если введенные размеры матрицы некорректны (n или m < 0, или количество ненулевых элементов больше, чем общее количество элементов матрицы),
 либо OK, если ввод успешен.
 */
int read_matrix(const char *file_name, double ***matrix, int *n, int *m, int *not_null)
{
    FILE *f;
    int rc = OK;
    int i = 0; int j = 0;
    double **buf = NULL;
    f = fopen(file_name, "r");
    if (f)
    {
        if (fscanf(f, "%d %d %d", n, m, not_null) == 3)
        {
            if (*n > 0 && *m > 0 && *not_null > 0 && *not_null <= (*n) * (*m))
            {
                buf = allocate_matrix(*n, *m);
                if (buf)
                {
                    for (int k = 0; k < *not_null && rc == OK; k++)
                    {
                        if (fscanf(f, "%d %d", &i, &j) == 2 && i >= 0 && j >= 0 && i < *n && j < *m)
                        {
                            if ((buf[i][j] != 0) || fscanf(f, "%lf", &buf[i][j]) != 1 || buf[i][j] == 0)
                                rc = INPUT_ERROR;
                        }
                        else
                            rc = INPUT_ERROR;
                        if (k + 1 != *not_null && feof(f) != 0)
                            rc = INPUT_ERROR;
                    }
                    if (rc == INPUT_ERROR)
                        free_matrix(buf, *n);
                    else
                        *matrix = buf;
                }
                else
                    rc = MEMORY_ERROR;
            }
            else
                rc = N_M_PARAMS_ERROR;
        }
        else
            rc = INPUT_ERROR;
        fclose(f);
    }
    else
        return FILE_OPEN_ERROR;
    return rc;
}

int coordinate_row(int *not_null_b, int *row_size, double *buf2)
{
    int i;
    int rc = OK;
    printf("\nEnter the elements in coordinate format.\nPlease enter the number of not null elements:\n");
    if (scanf("%d", not_null_b) == 1 && *not_null_b > 0 && *not_null_b <= *row_size)
    {
        printf("Enter the elements in coordinate format (indexes starts from 0!):\n[index] [element]\n");
        for (int k = 0; k < *not_null_b && rc == OK; k++)
        {
            printf("Enter elem: ");
            if (scanf("%d", &i) == 1 && i >= 0 && i < *row_size)
            {
                if ((buf2[i] != 0) || scanf("%lf", &buf2[i]) != 1 || buf2[i] == 0)
                    rc = INPUT_ERROR;
            }
            else
                rc = INPUT_ERROR;
        }
    }
    else
        rc = INPUT_ERROR;
    return rc;
}

int coordinate_matrix(int *not_null_a, int *n, int *m, double **buf)
{
    int i, j;
    int rc = OK;
    printf("\nEnter the elements in coordinate format.\nPlease enter the number of not null elements:\n");
    if (scanf("%d", not_null_a) == 1 && *not_null_a > 0 && *not_null_a <= ((*n) * (*m)))
    {
        printf("Enter the elements in coordinate format (indexes starts from 0!):\n[index] [index] [element]\n");
        for (int k = 0; k < *not_null_a && rc == OK; k++)
        {
            printf("Enter elem: ");
            if (scanf("%d %d", &i, &j) == 2 && i >= 0 && j >= 0 && i < *n && j < *m)
            {
                if ((buf[i][j] != 0) || scanf("%lf", &buf[i][j]) != 1 || buf[i][j] == 0)
                    rc = INPUT_ERROR;
            }
            else
                rc = INPUT_ERROR;
        }
    }
    else
        rc = INPUT_ERROR;
    return rc;
}

int input_byhand(double ***matrix, int *n, int *m, double **row, int *row_size, int *not_null_a, int *not_null_b)
{
    int rc = OK;
    double **buf = NULL;
    double *buf2 = NULL;
    int choice;
    printf("Input the size of the row-vector:\n");
    if (scanf("%d", row_size) == 1)
    {
        if (*row_size <= 0)
            return N_M_PARAMS_ERROR;
        buf2 = calloc((*row_size), sizeof(double));
        if (buf2)
        {
            if (*row_size <= 5)
            {
                printf("Enter the elements in ordinary format (1) or in coordinate format (2)?\nChoose 1 or 2: ");
                if (scanf("%d", &choice) == 1)
                {
                    if (choice == 1)
                    {
                        for (int i = 0; i < *row_size; i++)
                        {
                            printf("Enter row_vector[%d]: ", i);
                            if (scanf("%lf", &buf2[i]) != 1)
                            {
                                printf("Incorrect input");
                                free(buf2);
                                return INPUT_ERROR;
                            }
                            if (buf2[i] != 0)
                                (*not_null_b)++;
                        }
                    }
                    else if (choice == 2)
                        rc = coordinate_row(not_null_b, row_size, buf2);
                    else
                        rc = INPUT_ERROR;
                }
                else
                    rc = INPUT_ERROR;
            }
            else
                rc = coordinate_row(not_null_b, row_size, buf2);

            if (rc == INPUT_ERROR)
            {
                printf("Input error.\n");
                free(buf2);
                return rc;
            }
            else
                *row = buf2;
        }
        else
        {
            printf("Memory error.\n");
            return MEMORY_ERROR;
        }
    }
    else
    {
        printf("Input error.\n");
        return INPUT_ERROR;
    }

    printf("Input the size of the matrix (format:[n] [m]):\n");
    if (scanf("%d %d", n, m) == 2)
    {
        if (*n <= 0 || *m <= 0)
        {
            free(buf2);
            return N_M_PARAMS_ERROR;
        }
        buf = allocate_matrix(*n, *m);
        if (buf)
        {
            if (*n <= 5 && *m < 5)
            {
                printf("Enter the elements in ordinary format (1) or in coordinate format (2)?\nChoose 1 or 2: ");
                if (scanf("%d", &choice) == 1)
                {
                    if (choice == 1)
                    {
                        for (int i = 0; i < *n; i++)
                        {
                            for (int j = 0; j < *m; j++)
                            {
                                printf("Enter matrix[%d][%d]: ", i, j);
                                if (scanf("%lf", &buf[i][j]) != 1)
                                {
                                    printf("Incorrect input");
                                    free(buf2);
                                    free_matrix(buf, *n);
                                    return INPUT_ERROR;
                                }
                                if (buf[i][j] != 0)
                                    (*not_null_a)++;
                            }
                        }
                    }
                    else if (choice == 2)
                        coordinate_matrix(not_null_a, n, m, buf);
                    else
                        rc = INPUT_ERROR;
                }
                else
                    rc = INPUT_ERROR;
            }
            else
                coordinate_matrix(not_null_a, n, m, buf);
            if (rc == INPUT_ERROR)
            {
                printf("Input error.\n");
                free(buf2);
                free_matrix(buf, *n);
                return rc;
            }
            else
                *matrix = buf;
        }
        else
        {
            printf("Memory error.\n");
            free(buf2);
            return MEMORY_ERROR;
        }
    }
    else
    {
        printf("Input error.\n");
        free(buf2);
        return INPUT_ERROR;
    }
    return OK;
}

void print_matrix(double **matrix, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%.2lf ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}
