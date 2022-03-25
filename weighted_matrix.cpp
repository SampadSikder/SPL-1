#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include "print_matrix.h"
#include "matrix_operations.h"

using namespace std;
void E_step(double **Y, double **U, double **V, double **X, double **W, int row, int k, int col)
{
    double *one_matrix[row];
    for (int i = 0; i < row; i++)
    {
        one_matrix[i] = (double *)malloc(col * sizeof(double));
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            one_matrix[i][j] = 1;
        }
    }
    // complement of weight matrix
    double *one_minus_weight[row];
    for (int i = 0; i < row; i++)
    {
        one_minus_weight[i] = (double *)malloc(col * sizeof(double));
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            one_minus_weight[i][j] = one_matrix[i][j] - W[i][j];
        }
    }
    for (int i = 0; i < row; i++)
    {
        free(one_matrix[i]);
    }

    double *UVT[row];

    for (int i = 0; i < row; i++)
    {
        UVT[i] = (double *)malloc(col * sizeof(double));
    }

    multiply(UVT, U, V, row, k, col);
    print_matrix(UVT, row, col);

    double *second_part[row];

    for (int i = 0; i < row; i++)
    {
        second_part[i] = (double *)malloc(col * sizeof(double));
    }

    multiply_element_wise(second_part, one_minus_weight, UVT, row, col);

    for (int i = 0; i < row; i++)
    {
        free(one_minus_weight[i]);
    }

    for (int i = 0; i < row; i++)
    {
        free(UVT[i]);
    }

    print_matrix(second_part, row, col);
}

int main()
{
    double *matrix[N];
    int row, col;

    cout << "Enter number of rows and columns" << endl;
    cin >> row >> col;

    for (int i = 0; i < row; i++)
        matrix[i] = (double *)malloc(col * sizeof(double));

    cout << "Enter the matrix" << endl;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> matrix[i][j];
        }
    }
    double *weighted_matrix[N];

    for (int i = 0; i < row; i++)
        weighted_matrix[i] = (double *)malloc(col * sizeof(double));

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (matrix[i][j] == -1)
            {
                weighted_matrix[i][j] = 0;
            }
            else
            {
                weighted_matrix[i][j] = 1;
            }
        }
    }
    cout << "Weighted matrix: " << endl;
    print_matrix(weighted_matrix, row, col);

    // adding standard epsilon value to weighted matrix
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (matrix[i][j] == -1)
            {
                weighted_matrix[i][j] = EPSILON;
            }
        }
    }
    int k;
    printf("Enter the dimension: ");
    cin >> k;
    // filled in matrix calculation
    double *Y[N], *W[row], *H[col];

    for (int i = 0; i < row; i++)
        W[i] = (double *)malloc(k * sizeof(double));
    for (int i = 0; i < k; i++)
        H[i] = (double *)malloc(col * sizeof(double));

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < k; j++)
        {
            W[i][j] = Rand_number_generator(); // send to random number generator
        }
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < col; j++)
        {
            H[i][j] = Rand_number_generator(); // send to random number generator
        }
    }

    // E steo if EM-WNMF

    E_step(Y, W, H, matrix, weighted_matrix, row, k, col);
}