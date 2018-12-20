#ifndef PROCESS_H
#define PROCESS_H

typedef struct edge
{
    int row;
    int column;
} edge_t;

void BFS(int *visited, int start, int **matr, int n);
void put_edges(int **matrix, int n, edge_t **arr_edg, int *count_edges);

#endif // PROCESS_H
