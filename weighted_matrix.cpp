#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include "print_matrix.h"
#include "matrix_operations.h"

using namespace std;
void M_step_V_update(double **Y, double **U, double **V, double **X, double **W, int row, int k, int col)
{
    double *transpose_Y[col];
    for (int i = 0; i < col; i++)
    {
        transpose_Y[i] = (double *)malloc(row * sizeof(double));
    }
    transpose(Y, transpose_Y, row, col);
    double *numerator[col];
    for (int i = 0; i < col; i++)
    {
        numerator[i] = (double *)malloc(k * sizeof(double));
    }
    multiply(numerator, transpose_Y, U, col, row, k);
    for (int i = 0; i < col; i++)
    {
        free(transpose_Y[i]);
    }
    // print_matrix(numerator, col, k);

    double *transpose_V[col], *transpose_U[k];

    for (int i = 0; i < col; i++)
    {
        transpose_V[i] = (double *)malloc(k * sizeof(double));
    }
    for (int i = 0; i < k; i++)
    {
        transpose_U[i] = (double *)malloc(row * sizeof(double));
    }
    transpose(V, transpose_V, k, col);
    transpose(U, transpose_U, row, k);
    double *denominator_p_1[col];

    for (int i = 0; i < col; i++)
    {
        denominator_p_1[i] = (double *)malloc(row * sizeof(double));
    }
    multiply(denominator_p_1, transpose_V, transpose_U, col, k, row);
    for (int i = 0; i < k; i++)
    {
        free(transpose_U[i]);
    }
    // print_matrix(denominator_p_1, col, row);

    double *denominator[col];
    for (int i = 0; i < col; i++)
    {
        denominator[i] = (double *)malloc(k * sizeof(double));
    }
    multiply(denominator, denominator_p_1, U, col, row, k);
    // print_matrix(denominator, col, k);
    double *second_part[col];
    for (int i = 0; i < col; i++)
    {
        second_part[i] = (double *)malloc(k * sizeof(double));
    }
    divide_element_wise(second_part, numerator, denominator, col, k);
    // print_matrix(second_part, col, k);

    double *new_transpose_V[col];
    for (int i = 0; i < col; i++)
    {
        new_transpose_V[i] = (double *)malloc(k * sizeof(double));
    }
    multiply_element_wise(new_transpose_V, transpose_V, second_part, col, k);
    print_matrix(new_transpose_V, col, k);

    transpose(new_transpose_V, V, col, k);
    print_matrix(V, k, col);
}
void M_step_U_update(double **Y, double **U, double **V, double **X, double **W, int row, int k, int col)
{
    double *numerator[row], *transpose_V[col];
    for (int i = 0; i < col; i++)
    {
        transpose_V[i] = (double *)malloc(k * sizeof(double));
    }
    transpose(V, transpose_V, k, col);
    for (int i = 0; i < row; i++)
    {
        numerator[i] = (double *)malloc(k * sizeof(double));
    }
    multiply(numerator, Y, transpose_V, row, col, k);
    // print_matrix(numerator, row, k);

    double *denominator_p_1[row], *denominator[row];

    for (int i = 0; i < row; i++)
    {
        denominator_p_1[i] = (double *)malloc(col * sizeof(double));
    }
    multiply(denominator_p_1, U, V, row, k, col);

    for (int i = 0; i < row; i++)
    {
        denominator[i] = (double *)malloc(k * sizeof(double));
    }
    multiply(denominator, denominator_p_1, transpose_V, row, col, k);
    for (int i = 0; i < col; i++)
    {
        free(transpose_V[i]);
    }
    for (int i = 0; i < row; i++)
    {
        free(denominator_p_1[i]);
    }

    print_matrix(denominator, row, k);

    double *second_part[row];

    for (int i = 0; i < row; i++)
    {
        second_part[i] = (double *)malloc(k * sizeof(double));
    }
    divide_element_wise(second_part, numerator, denominator, row, k);
    print_matrix(second_part, row, k);

    double *new_U[row];
    for (int i = 0; i < row; i++)
    {
        new_U[i] = (double *)malloc(k * sizeof(double));
    }
    multiply_element_wise(new_U, U, second_part, row, k);
    copy_matrix(new_U, U, row, k);
    print_matrix(U, row, k);
}
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
    // print_matrix(UVT, row, col);

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

    // print_matrix(second_part, row, col);

    double *first_part[row];

    for (int i = 0; i < row; i++)
    {
        first_part[i] = (double *)malloc(col * sizeof(double));
    }

    multiply_element_wise(first_part, W, X, row, col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            Y[i][j] = first_part[i][j] + second_part[i][j];
        }
    }
}

int main()
{
    freopen("in2.txt", "r", stdin);
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
    // print_matrix(weighted_matrix, row, col);

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
        Y[i] = (double *)malloc(col * sizeof(double));

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
    // print_matrix(Y, row, col);
    // M_step_U_update(Y, W, H, matrix, weighted_matrix, row, k, col);
    M_step_V_update(Y, W, H, matrix, weighted_matrix, row, k, col);
}