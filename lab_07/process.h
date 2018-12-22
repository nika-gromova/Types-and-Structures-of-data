#ifndef PROCESS_H
#define PROCESS_H

typedef struct edge
{
    int row;
    int column;
} edge_t;

void BFS(int *visited, int start, int **matr, int n);
void put_edges(int **matrix, int n, edge_t *arr_edg, int count_edges);
void zero(int *arr, int n);
int find_del(edge_t *edges, int count_edges, int **matrix, int n, int *visited, int *del_1, int *del_2, int *del_3, int a, int b);

#endif // PROCESS_H
