#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "io.h"
#include "defines.h"
#include "allocate.h"
#include "process.h"


unsigned long long tick(void)
{
    unsigned long d;
    __asm__ __volatile__ ("rdtsc" : "=A"(d));
    return d;
}

void intro(void)
{
    printf("Hello! This is a programme for multiplication of sparse row-vector by sparse matrix.\n"
           "Plese first choose the way of inputing the data (by-hand or read from the file). Data in file should be only in coordinate format, Indexes starts from 0!\n"
           "Then choose the format of input by-hand: ordinary or coordinate (for matrix size more than 5 the format should be coordinate).\n"
           "If you've chosen input from a file, than input first the name for a file with row-vector and than another name for a file with matrix.\n"
           "The format of the file: first string includes number of rows, number of columns and number of not-null elements.\n"
           "Each next string includes index of the row, index of the column and the elements of the matrix.\n"
           "Example:\n"
           "2 2 3\n"
           "0 1 4\n"
           "1 0 -9\n"
           "1 1 7\n"
           "This example prescribes such matrix:\n"
           "0 4\n"
           "-9 7\n"
           "For the file for row-vector is almost the same, but you have only to point the size of the vector and nuber of nit-null elements, then the index and the elementd\n"
           "Example:\n"
           "5 3\n"
           "1 5\n"
           "2 -9\n"
           "4 3.3\n"
           "This example prescribes such row-vector:\n"
           "0 5 -9 0 3.3\n\n"
           "The result of the calculation will be available in sparse format.\n"
           "If the size of result array won't exceed 5, than it will be given in ordinary format too.\n\n");
}

int create_rand_matrix(int n, int m, int proc)
{
    FILE *f = fopen("in_3_2.txt", "w");
    if (!f)
        return INPUT_ERROR;
    if (n <= 1 || m <= 1)
        return INPUT_ERROR;
    if (proc < 1 || proc > 100)
        return INPUT_ERROR;

    srand(time(NULL));
    int index_i = 0, index_j = m - 1;
    double elem;
    int not_null_elements = ((n * m) * proc) / 100;
    fprintf(f, "%d %d %d\n", n, m, not_null_elements);
    for (int i = 0; i < not_null_elements; i++)
    {
        elem = 1 + rand() % 100;
        fprintf(f, "%d %d %.2lf\n", index_i, index_j, elem);
        if (index_j - 1 < 0)
        {
            index_i++;
            index_j = m - 1;
        }
        else
            index_j--;
    }
    fclose(f);
    return OK;
}
int create_rand_vectors(int m, int proc)
{
    FILE *f = fopen("in_3_1.txt", "w");
    if (!f)
        return INPUT_ERROR;
    if (m <= 1)
        return INPUT_ERROR;
    if (proc < 1 || proc > 100)
        return INPUT_ERROR;

    srand(time(NULL));
    int index_j = 0;
    double elem;
    int not_null_elements = (m * proc) / 100;
    fprintf(f, "%d %d\n", m, not_null_elements);
    for (int i = 0; i < not_null_elements; i++)
    {
        elem = 1 + rand() % 100;
        fprintf(f, "%d %.2lf\n", index_j, elem);
        if (index_j + 1 > m - 1)
            index_j = 0;
        else
            index_j++;
    }
    fclose(f);
    return OK;
}

int main(void)
{
    int rc = OK;
    double **matrix = NULL;
    int n, m;
    double *row_vector = NULL;
    int row_size;

    double *A = NULL;
    //int n_a;
    int *IA = NULL, *JA = NULL;
    int not_null_a = 0;//, column_num, n_b;
    double *B = NULL;
    int *IB = NULL;
    int not_null_b = 0;

    int choice = 0;
    intro();
    create_rand_matrix(100, 100, 90);
    create_rand_vectors(100, 90);
    printf("Input data: by-hand (1) or from file (2) or create your own file (3)\nChoose input: ");
    if (scanf("%d", &choice) == 1)
    {
        if (choice == 3)
        {
            int proc;
            printf("Input the size of row vector (n > 0) and percent (1 - 100): [n] [%c]\n", '%');
            if (scanf("%d %d", &row_size, &proc) == 2)
            {
                rc = create_rand_vectors(row_size, proc);
                if (rc != OK)
                {
                    printf("Invalid parameters.\n");
                    return rc;
                }
                printf("Input the size of matrix (n > 0, m > 0) and percent (1 - 100): [n] [m] [%c]\n", '%');
                if (scanf("%d %d %d", &n, &m, &proc) == 3)
                {
                    rc = create_rand_matrix(n, m, proc);
                    if (rc != OK)
                    {
                        printf("Invalid parameters.\n");
                        return rc;
                    }
                    rc = read_row("in_3_1.txt", &row_vector, &row_size, &not_null_b);
                    if (rc == OK)
                    {
                        rc = read_matrix("in_3_2.txt", &matrix, &n, &m, &not_null_a);
                        if (rc != OK)
                        {
                            free(row_vector);
                            printf("Something wrong with file or data in file. Try again later %d:)\n", rc);
                            return READ_ERROR;
                        }
                    }
                    else
                    {
                        printf("Something wrong with file or data in file. Try again later :)\n");
                        return READ_ERROR;
                    }
                }
                else
                    rc = INPUT_ERROR;
            }
            else
                rc = INPUT_ERROR;

        }
        else if (choice == 1)
        {
            rc = input_byhand(&matrix, &n, &m, &row_vector, &row_size, &not_null_a, &not_null_b);
            if (rc != OK)
                return rc;
        }
        else if (choice == 2)
        {
            char file_row[50], file_matrix[50];
            printf("\n!!!All data in files should be in coordinate format and indexes starts from 0!!!");
            printf("\nPlease enter name of the file with row-vector: ");
            if (scanf("%s", file_row) == 1)
            {
                printf("\nPlease enter name of the file with matrix: ");
                if (scanf("%s", file_matrix) == 1)
                {
                    rc = read_row(file_row, &row_vector, &row_size, &not_null_b);
                    if (rc == OK)
                    {
                        rc = read_matrix(file_matrix, &matrix, &n, &m, &not_null_a);
                        if (rc != OK)
                        {
                            free(row_vector);
                            printf("Something wrong with file or data in file. Try again later %d:)\n", rc);
                            return READ_ERROR;
                        }
                    }
                    else
                    {
                        printf("Something wrong with file or data in file. Try again later :)\n");
                        return READ_ERROR;
                    }
                }
                else
                    rc = INPUT_STR_ERROR;
            }
            else
                rc = INPUT_STR_ERROR;
        }
        else
            rc = INPUT_ERROR;
    }
    else
        rc = INPUT_ERROR;

    if (rc == INPUT_ERROR)
    {
        printf("Incorrect input.\n");
        return rc;
    }
    else if (rc == INPUT_STR_ERROR)
    {
        printf("Incorrect input of file names.\n");
        return rc;
    }

    if (fabs(n - row_size) > EPS)
    {
        printf("Impossible to perform a multiplication for 1 x %d and %d x %d\n", row_size, n, m);
        free_matrix(matrix, n);
        free(row_vector);
        return N_M_PARAMS_ERROR;
    }
    rc = partioning(matrix, &A, &IA, &JA, not_null_a, n, m);
    if (rc == OK)
    {
        rc = partioning_vector(row_vector, &B, &IB, row_size, not_null_b);
        if (rc == OK)
        {
            double *res1 = malloc(m * sizeof(double));
            double *res_N = NULL;
            int *Ires = NULL;
            int not_null_res = 0;
            if (res1)
            {
                rc = multiplication(A, IA, JA, row_size, m, B, IB, not_null_b, res1, &not_null_res);
                if (rc == OK)
                {
                    printf("\nRESULT:\n");
                    rc = partioning_vector(res1, &res_N, &Ires, m, not_null_res);
                    if (rc == OK)
                    {
                        if (not_null_res == 0)
                            printf("all elements in result vector are null");
                        else
                        {
                            printf("\nSparce matrix format:\n");
                            printf("indexes | values\n");
                            for (int i = 0; i < not_null_res; i++)
                                printf("%7d | %.2lf\n", Ires[i], res_N[i]);
                            printf("\n");
                        }

                        if (m < 6)
                        {
                            printf("\n\nResult vector in ordinary format: ");
                            for (int i = 0; i < m; i++)
                                printf("%.2lf ", res1[i]);
                        }
                        free(res_N);
                        free(Ires);
                    }
                    double *res2 = malloc(m * sizeof(double));
                    if (res2)
                    {
                        unsigned long long t1, t2, t3, t4;
                        t1 = tick();
                        for (int i = 0; i < 10 && rc == OK; i++)
                            rc = mult_vector_matrix(matrix, n, m, row_vector, row_size, res2);
                        t2 = tick();
                        printf("\n\nTime measurements for processing standart method of multiplication: %I64u\n", (t2 - t1) / 10);
                        printf("memory space = %d\n", (n * m * sizeof(double) + m * sizeof(double)));

                        t3 = tick();
                        for (int i = 0; i < 10 && rc == OK; i++)
                            rc = multiplication(A, IA, JA, row_size, m, B, IB, not_null_b, res1, &not_null_res);
                        t4 = tick();
                        printf("\n\nTime measurements for processing method of sparse matrix multiplication: %I64u\n", (t4 - t3) / 10);
                        printf("memory space = %d", (not_null_a * sizeof(double) + not_null_a * sizeof(int) + (m + 1) * sizeof(int) +\
                                                        not_null_b * sizeof(double) + not_null_b * sizeof(int) + n * sizeof(int)));
                        free(res2);
                    }
                }
                free(res1);
            }
            else
                printf("Memory error");
            free(B);
            free(IB);
        }
        free(A);
        free(IA);
        free(JA);
    }
    free(row_vector);
    free_matrix(matrix, n);
    return rc;
}
