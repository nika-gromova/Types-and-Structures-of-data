#include <stdio.h>
#include <stdlib.h>
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

void zero(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = 0;
}

int main(void)
{
    int n = 6;
    int **matrix = allocate_matrix(n, n);
    edge_t *edges = NULL;
    int del_1 = -1, del_2 = -1, del_3 = -1;
    int find = 1;
    int count_edges;
    int visited[6];
    zero(visited, 6);
    if (matrix)
    {
        matrix[0][1] = 1;
        matrix[0][5] = 1;
        matrix[1][0] = 1;
        matrix[1][2] = 1;
        matrix[1][5] = 1;
        matrix[2][1] = 1;
        matrix[2][3] = 1;
        matrix[2][4] = 1;
        matrix[3][2] = 1;
        matrix[3][4] = 1;
        matrix[4][2] = 1;
        matrix[4][3] = 1;
        matrix[4][5] = 1;
        matrix[5][0] = 1;
        matrix[5][1] = 1;
        matrix[5][4] = 1;
        matrix[1][4] = 1;
        matrix[4][1] = 1;
        matrix[5][2] = 1;
        matrix[2][5] = 1;
        matrix[1][3] = 1;
        matrix[3][1] = 1;
        matrix[3][5] = 1;
        matrix[5][3] = 1;
        print_matrix(matrix, n);
        put_edges(matrix, 6, &edges, &count_edges);
        printf("num of edges: %d\n", count_edges);
        //print_edges(edges, count_edges);
        for (int i = 0; i < count_edges && find; i++)
        {
            for (int j = i + 1; j < count_edges && j > i && find; j++)
            {
                for (int k = j + 1; k < count_edges && k > j && find; k++)
                {
                    matrix[edges[i].row][edges[i].column] = 0;
                    matrix[edges[j].row][edges[j].column] = 0;
                    matrix[edges[k].row][edges[k].column] = 0;
                    matrix[edges[i].column][edges[i].row] = 0;
                    matrix[edges[j].column][edges[j].row] = 0;
                    matrix[edges[k].column][edges[k].row] = 0;


                    del_1 = i;
                    del_2 = j;
                    del_3 = k;
                    BFS(visited, 1, matrix, n);
                    if (visited[3] == 0)
                        find = 0;
                    else
                    {
                        matrix[edges[i].row][edges[i].column] = 1;
                        matrix[edges[j].row][edges[j].column] = 1;
                        matrix[edges[k].row][edges[k].column] = 1;
                        matrix[edges[i].column][edges[i].row] = 1;
                        matrix[edges[j].column][edges[j].row] = 1;
                        matrix[edges[k].column][edges[k].row] = 1;
                        del_1 = -1;
                        del_2 = -1;
                        del_3 = -1;
                    }
                    zero(visited, 6);
                }
            }
        }
        if (find == 0)
            printf("%d %d\n%d %d\n%d %d\n", edges[del_1].row, edges[del_1].column, edges[del_2].row, edges[del_2].column, edges[del_3].row, edges[del_3].column);
        else
            printf("no variants\n");
        free(edges);
        free_matrix(matrix, 3);
    }
    return 0;
}
