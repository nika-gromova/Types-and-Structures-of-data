#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "process.h"
#include "allocate.h"

void print_matrix(int ** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
}

void print_edges(edge_t *edges, int m)
{
    for (int i = 0; i < m; i++)
        printf("%d %d\n", edges[i].row, edges[i].column);
}



void zero_matrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0;
}

unsigned long long tick(void)
{
    unsigned long d;
    __asm__ __volatile__ ("rdtsc" : "=A"(d));
    return d;
}

void info(void)
{
    printf("1 - load incident matrix from file;\n");
    printf("2 - input incident matrix in coordinate format;\n");
    printf("3 - print matrix;\n");
    printf("4 - form graph in graphic view;\n");
    printf("5 - 'closing roads' and outlays;\n");
    printf("6 - exit.\n");
}

void free_all(int **matrix, int *visited, int *n, int *count_edges, edge_t *edges)
{
    free_matrix(matrix, *n);
    free(visited);
    free(edges);
    *count_edges = 0;
    *n = 0;
}

int read_data(FILE *f, int ***matrix, int *n, int *not_null)
{
    int **buf = NULL;
    int rc = OK;
    int i = 0, j = 0;
    fscanf(f, "%d %d", n, not_null);
    if (*n > 0 && *not_null > 0 && *not_null <= (*n) * (*n))
    {
        buf = allocate_matrix(*n, *n);
        if (buf)
        {
            zero_matrix(buf, *n);
            for (int k = 0; k < *not_null && rc == OK; k++)
            {
                if (fscanf(f, "%d %d", &i, &j) == 2 && i >= 0 && j >= 0 && i < *n && j < *n)
                {
                    if ((buf[i][j] != 0))
                        rc = INPUT_ERROR;
                    else
                    {
                        buf[i][j] = 1;
                        buf[j][i] = 1;
                    }
                }
                else
                    rc = INPUT_ERROR;
            }
            if (rc == INPUT_ERROR)
                free_matrix(buf, *n);
            else
                *matrix = buf;
        }
        else
            return MEMORY_ERROR;
    }
    else
        return INPUT_ERROR;
    return rc;
}

int export_to_dot(int **matrix, int n, FILE *f, const char *name)
{
    if (matrix == NULL)
    {
        printf("matrix is empty.\n");
        return 0;
    }
    fprintf(f, "graph %s {\n", name);
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "%d;\n", i);
        for (int j = 0; j < n; j++)
            if (j > i)
                if (matrix[i][j] == 1)
                    fprintf(f, "%d -- %d;\n", i, j);
    }
    fprintf(f, "}\n");
    return 1;
}

int main(void)
{
    int rc = OK;

    int **matrix = NULL;
    int n = 0;
    edge_t *edges = NULL;
    int count_edges;
    int *visited = NULL;

    int del_1, del_2, del_3;

    int A, B;

    char file[20];
    char buf[20];
    char *end = NULL;
    FILE *f;

    int choice = 0;

    unsigned long int t1, t2;

    while (choice == 0)
    {
        info();
        if (scanf("%s", buf) == 1)
        {
            choice = strtol(buf, &end, 10);
            if (*end == '\0' && choice > 0 && choice < 10)
            {
                if (choice == 1)
                {
                    free_all(matrix, visited, &n, &count_edges, edges);
                    printf("Input file name:\n");
                    scanf("%s", file);
                    f = fopen(file, "r");
                    if (f)
                    {
                        rc = read_data(f, &matrix, &n, &count_edges);
                        if (rc == OK)
                        {
                            printf("loaded!\n");
                            choice = 0;
                        }
                        else
                            printf("incorrect input:( try again\n");
                        fclose(f);
                    }
                    else
                    {
                        printf("error in openning file ;( \n");
                        choice = 0;
                    }
                }
                if (choice == 2)
                {
                    free_all(matrix, visited, &n, &count_edges, edges);
                    printf("input number of nodes of the graph (n) and number of paths (m) and then input connected nodes:\n");
                    printf("Example:\n5 2\n1 4\n2 3\n");
                    rc = read_data(stdin, &matrix, &n, &count_edges);
                    if (rc == OK)
                    {
                        printf("loaded!\n");
                        choice = 0;
                    }
                    else
                        printf("incorrect input:( try again\n");
                }
                if (choice == 3)
                {
                    print_matrix(matrix, n);
                    choice = 0;
                }
                if (choice == 4)
                {
                    f = fopen("graph.gv", "w");
                    if (f)
                    {
                        if (export_to_dot(matrix, n, f, "my_graph"))
                            printf("saved in graph.gv!\n");
                        else
                            printf("error in saving to 'graph.gv'\n");
                        fclose(f);
                    }
                    else
                        printf("someting wrong with the file\n");
                    choice = 0;
                }
                if (choice == 5)
                {
                    printf("Input number of start node (A):\n");
                    scanf("%s", buf);
                    A = strtol(buf, &end, 10);
                    if (*end == '\0' && A >= 0 && A < n)
                    {
                        printf("Input number of final node (B):\n");
                        scanf("%s", buf);
                        B = strtol(buf, &end, 10);
                        if (*end == '\0' && B >= 0 && B < n)
                        {
                            edges = calloc(count_edges, sizeof(edge_t));
                            if (edges)
                            {
                                visited = calloc(n, sizeof(int));
                                if (visited)
                                {
                                    zero(visited, n);
                                    put_edges(matrix, n, edges, count_edges);
                                    t1 = tick();
                                    rc = find_del(edges, count_edges, matrix, n, visited, &del_1, &del_2, &del_3, A, B);
                                    t2 = tick();
                                    if (rc)
                                        printf("There are no variants to close 3 paths and make B inaccessible from A.\n");
                                    else
                                    {
                                        printf("There is a variant to close 3 paths and make B inaccessible from A.\n");
                                        printf("\nClosing paths:\n");
                                        printf("%d <-> %d\n", edges[del_1].row, edges[del_1].column);
                                        printf("%d <-> %d\n", edges[del_2].row, edges[del_2].column);
                                        printf("%d <-> %d\n", edges[del_3].row, edges[del_3].column);
                                    }
                                    printf("\nTime outlays: %lu\n", (unsigned long) (t2 - t1));
                                    free(visited);
                                    visited = NULL;
                                }
                                free(edges);
                                edges = NULL;
                            }
                            else
                                printf("memory error\n");
                        }
                        else
                            printf("incorrect input\n");
                    }
                    else
                        printf("incorrect input\n");

                    choice = 0;
                }
                if (choice == 6)
                {
                    printf("Exit.\n");
                }
            }
            else
                printf("wrong menu choice\n");
        }
        else
            printf("input again:\n");
    }

    free_all(matrix, visited, &n, &count_edges, edges);
    return 0;
}
