#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include "print_matrix.h"
#include "matrix_operations.h"
#include "my_library.h"

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
    free_matrix(transpose_Y, col);

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
    free_matrix(transpose_U, k);

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
    free_matrix(transpose_V, col);
    free_matrix(denominator_p_1, row);

    print_matrix(denominator, row, k);

    double *second_part[row];

    for (int i = 0; i < row; i++)
    {
        second_part[i] = (double *)malloc(k * sizeof(double));
    }
    divide_element_wise(second_part, numerator, denominator, row, k);
    // print_matrix(second_part, row, k);

    double *new_U[row];
    for (int i = 0; i < row; i++)
    {
        new_U[i] = (double *)malloc(k * sizeof(double));
    }
    multiply_element_wise(new_U, U, second_part, row, k);
    copy_matrix(new_U, U, row, k);
    // print_matrix(U, row, k);
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
    free_matrix(one_matrix, row);

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

    free_matrix(one_minus_weight, row);
    free_matrix(UVT, row);

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
                matrix[i][j] = STANDARD_EPSILON;
            }
        }
    }
    normalize(matrix, row, col);
    int k;
    printf("Enter the dimension: ");
    cin >> k;
    // filled in matrix calculation
    double *Y[N], *W[row], *H[col], *V[row];

    for (int i = 0; i < row; i++)
        W[i] = (double *)malloc(k * sizeof(double));
    for (int i = 0; i < k; i++)
        H[i] = (double *)malloc(col * sizeof(double));
    for (int i = 0; i < row; i++)
        Y[i] = (double *)malloc(col * sizeof(double));
    for (int i = 0; i < row; i++)
        V[i] = (double *)malloc(col * sizeof(double));

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

    // E step if EM-WNMF

    E_step(Y, W, H, matrix, weighted_matrix, row, k, col);
    // print_matrix(Y, row, col);
    int counter = 1;
    printf("Initial cost: ");
    // cost function
    double cost = cost_function(matrix, V, row, col);
    stck.push(cost);
    while (cost > 0.05)
    {

        if ((counter % 2) == 0)
        {
            M_step_U_update(Y, W, H, matrix, weighted_matrix, row, k, col);
            cout << "New H:" << endl;
            print_matrix(H, k, col);
        }
        else
        {
            M_step_V_update(Y, W, H, matrix, weighted_matrix, row, k, col);
            cout << "New W: " << endl;
            print_matrix(W, row, k);
        }
        counter++;
        multiply(V, W, H, row, k, col);
        cost = cost_function(matrix, V, row, col);
        // local minima reached need to stop by calculating difference with previous error
        if (fabs(stck.top() - cost) <= EPSILON)
        {
            printf("%lf", stck.top() - cost);
            printf("Reached relative minima\n");
            break;
        }
        else
        {
            if (stck.pop())
            {
                stck.push(cost);
            }
        }
    }
    printf("Final cost: ");
    cout << cost_function(matrix, V, row, col) << endl;
    cout << "Final Second Matrix: " << endl;
    print_matrix(H, k, col);
    cout << "Final First Matrix: " << endl;
    print_matrix(W, row, k);
    cout << "Final Matrix: " << endl;
    print_matrix(V, row, col);
    return 0;
}