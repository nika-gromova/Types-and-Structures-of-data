#include <stdlib.h>

#include "defines.h"
#include "my_queue.h"
#include "process.h"

void BFS(int *visited, int start, int **matr, int n)
{
    queue_array_d queue;
    queue.cur_count = 0;
    queue.size = MAX_QUEUE_LEN;
    queue.in = 0;
    queue.out = 0;
    int tmp;
    int rc = push_arr(&queue, start);
    if (rc != OK)
        return;

    visited[start] = 1;
    while (queue.cur_count != 0)
    {
        pop_arr(&queue, &tmp);
        for (int i = 0; i < n; i++)
        {
            if (matr[tmp][i] == 1)
            {
                if (visited[i] == 0)
                {
                    visited[i] = 1;
                    push_arr(&queue, i);
                }
            }
        }
    }
}


void put_edges(int **matrix, int n, edge_t *arr_edg, int count_edges)
{
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j > i)
            {
                if (matrix[i][j] == 1)
                {
                    arr_edg[k].row = i;
                    arr_edg[k].column = j;
                    k++;
                }
            }
        }
    }
}

void zero(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = 0;
}

void zero_matrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = 0;
}

int find_del(edge_t *edges, int count_edges, int **matrix, int n, int *visited, int *del_1, int *del_2, int *del_3, int a, int b)
{
    int find = 1;
    if (count_edges <= 3)
    {
        zero_matrix(matrix, n);
        return -1;
    }
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

                *del_1 = i;
                *del_2 = j;
                *del_3 = k;
                BFS(visited, a, matrix, n);
                if (visited[b] == 0)
                    find = 0;
                else
                {
                    matrix[edges[i].row][edges[i].column] = 1;
                    matrix[edges[j].row][edges[j].column] = 1;
                    matrix[edges[k].row][edges[k].column] = 1;
                    matrix[edges[i].column][edges[i].row] = 1;
                    matrix[edges[j].column][edges[j].row] = 1;
                    matrix[edges[k].column][edges[k].row] = 1;
                    *del_1 = -1;
                    *del_2 = -1;
                    *del_3 = -1;
                }
                zero(visited, n);
            }
        }
    }
    return find;
}
