#ifndef PROCESS_H
#define PROCESS_H

#include <math.h>
#include <assert.h>

void mult(const int m1[], const int m2[], int n1, int n2, int res[], int len);
void reverse_arr(int arr[], int n);
int process(int M1[], int M2[], int n_1, int n_2, int i_point_1, int i_point_2, int *total_point,
            int P1, int P2, int *total_P, int sign_p_1, int sign_p_2, int *total_sign_P, int res[], int *len);

#endif // PROCESS_H
