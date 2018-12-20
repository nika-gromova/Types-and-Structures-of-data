#include <stdlib.h>
#include <stdio.h>

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
            if (matr[tmp][i] == 1 && visited[i] == 0)
            {
                push_arr(&queue, i);
                visited[i] = 1;
            }
        }
    }
}


void put_edges(int **matrix, int n, edge_t **arr_edg, int *count_edges)
{
    int k = 0;
    *count_edges = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (j > i)
                if (matrix[i][j] == 1)
                    (*count_edges)++;
    *arr_edg = calloc(*count_edges, sizeof(edge_t));
    if (*arr_edg)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (j > i)
                {
                    if (matrix[i][j] == 1)
                    {
                        (*arr_edg)[k].row = i;
                        (*arr_edg)[k].column = j;
                        k++;
                    }
                }
            }
        }
    }
}
