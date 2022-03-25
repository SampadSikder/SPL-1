#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include "print_matrix.h"
#include "matrix_operations.h"
using namespace std;

void update_H(double **W, double **H, double **V, int row, int k, int col)
{
    double *transpose_W[k];
    for (int i = 0; i < k; i++)
    {
        transpose_W[i] = (double *)malloc(row * sizeof(double));
    }
    // cout << "WT=";

    transpose(W, transpose_W, row, k);

    // print_matrix(transpose_W, k, row);

    double *WH[row];
    for (int i = 0; i < row; i++)
    {
        WH[i] = (double *)malloc(col * sizeof(double));
    }
    multiply(WH, W, H, row, k, col);

    print_matrix(WH, row, col);

    double *V_by_WH[row];
    // V/WH
    for (int i = 0; i < row; i++)
    {
        V_by_WH[i] = (double *)malloc(col * sizeof(double));
    }
    divide_element_wise(V_by_WH, V, WH, row, col);
    // cout << "V by WH";
    // print_matrix(V_by_WH, row, col);
    //   Clearing WH
    for (int i = 0; i < row; i++)
    {
        free(WH[i]);
    }

    // WT*(V/WH)
    double *numerator[k];
    for (int i = 0; i < k; i++)
    {
        numerator[i] = (double *)malloc(col * sizeof(double));
    }
    multiply(numerator, transpose_W, V_by_WH, k, row, col);

    for (int i = 0; i < row; i++)
    {
        free(V_by_WH[i]);
    }
    // Row summation of WT i.e column summation of W
    double *row_one_matrix[row]; // Matrix of 1 with 1 column
    for (int i = 0; i < row; i++)
    {
        row_one_matrix[i] = (double *)malloc(sizeof(double));
        row_one_matrix[i][0] = 1.0;
    }
    double *denominator[k]; // matrix
    for (int i = 0; i < k; i++)
    {
        denominator[i] = (double *)malloc(sizeof(double));
    }
    multiply(denominator, transpose_W, row_one_matrix, k, row, 1); // k* row and row* 1 dimension
    // print_matrix(denominator, k, 1);

    for (int i = 0; i < row; i++)
    {
        free(row_one_matrix[i]);
    }
    double *new_H[k];
    for (int i = 0; i < k; i++)
    {
        new_H[i] = (double *)malloc(col * sizeof(double));
    }
    // dividing each column with vector
    for (int j = 0; j < col; j++)
    {
        for (int i = 0; i < k; i++)
        {
            new_H[i][j] = numerator[i][j] / denominator[i][0];
        }
    }
    // print_matrix(new_H, k, col);
    double *updated_H[k];

    for (int i = 0; i < k; i++)
    {
        updated_H[i] = (double *)malloc(col * sizeof(double));
    }
    multiply_element_wise(updated_H, H, new_H, k, col);
    // print_matrix(updated_H, k, col);
    copy_matrix(updated_H, H, k, col);
}
void update_W(double **W, double **H, double **V, int row, int k, int col)
{
    double *WH[row];
    for (int i = 0; i < row; i++)
    {
        WH[i] = (double *)malloc(col * sizeof(double));
    }
    multiply(WH, W, H, row, k, col);
    // print_matrix(WH, row, col);
    double *V_by_WH[row];
    for (int i = 0; i < row; i++)
    {
        V_by_WH[i] = (double *)malloc(col * sizeof(double));
    }

    divide_element_wise(V_by_WH, V, WH, row, col);

    for (int i = 0; i < row; i++)
    {
        free(WH[i]);
    }

    double *transpose_H[col];
    for (int i = 0; i < col; i++)
    {
        transpose_H[i] = (double *)malloc(k * sizeof(double));
    }

    transpose(H, transpose_H, k, col);

    // divide_element_wise(V_by_WH, V, WH, row, col);

    double *numerator[row];

    for (int i = 0; i < row; i++)
    {
        numerator[i] = (double *)malloc(k * sizeof(double));
    }

    multiply(numerator, V_by_WH, transpose_H, row, col, k);
    // print_matrix(numerator, row, k);
    for (int i = 0; i < row; i++)
    {
        free(V_by_WH[i]);
    }

    double *col_one_matrix[1];

    col_one_matrix[0] = (double *)malloc(col * sizeof(double));

    for (int i = 0; i < 1; i++) // for some reason doesnt work without this loop
    {
        for (int j = 0; j < col; j++)
        {
            col_one_matrix[i][j] = 1.0;
        }
    }

    // print_matrix(col_one_matrix, 1, col);

    double *denominator[1];
    denominator[0] = (double *)malloc(k * sizeof(double));

    multiply(denominator, col_one_matrix, transpose_H, 1, col, k);

    // print_matrix(denominator, 1, k);

    double *new_W[row];

    for (int i = 0; i < row; i++)
    {
        new_W[i] = (double *)malloc(k * sizeof(double));
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < k; j++)
        {
            new_W[i][j] = numerator[i][j] / denominator[0][j];
        }
    }
    // print_matrix(new_W, row, k);

    double *updated_W[row];
    for (int i = 0; i < row; i++)
    {
        updated_W[i] = (double *)malloc(k * sizeof(double));
    }
    multiply_element_wise(updated_W, W, new_W, row, k);
    copy_matrix(updated_W, W, row, k);
    print_matrix(W, row, k);
}

int main()
{
    freopen("in2.txt", "r", stdin);
    double *matrix[N];
    int row, col, i, j, k;

    printf("Enter number of rows and cols: ");
    // Taking input
    cin >> row >> col; // m*n matrix

    for (int i = 0; i < row; i++)
        matrix[i] = (double *)malloc(col * sizeof(double));

    printf("Enter matrix: ");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
            cin >> matrix[i][j];
    }
    cout << "After normalization" << endl;

    normalize(matrix, row, col);

    // print_matrix(matrix, row, col);
    //  Generating two matrices using user input dimension and random number generator
    //   Dimension of broken matrix
    printf("Enter dimension: ");
    cin >> k;

    printf("Matrix broken and initialized using Gaussian dist: ");
    double *W[row], *H[k]; // broken down in m*k and k*n matrix

    for (int i = 0; i < row; i++)
        W[i] = (double *)malloc(k * sizeof(double));
    for (int i = 0; i < k; i++)
        H[i] = (double *)malloc(col * sizeof(double));

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < k; j++)
        {
            W[i][j] = Rand_number_generator(); // send to random number generator
        }
    }

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < col; j++)
        {
            H[i][j] = Rand_number_generator(); // send to random number generator
        }
    }

    printf("Print broken down matrices:\n");
    print_two_matrix(W, H, row, k, col);
    // multiplication
    double *V[row];
    for (int i = 0; i < row; i++)
        V[i] = (double *)malloc(col * sizeof(double));
    multiply(V, W, H, row, k, col);

    int counter = 1;
    printf("Initial cost: ");
    // cost function
    double cost = cost_function(matrix, V, row, col);

    // kulback-leibler divergence
    // update_H(W, H, matrix, row, k, col);
    // update_W(W, H, matrix, row, k, col);
    while (cost > 0.05)
    {

        if ((counter % 2) == 0)
        {
            update_H(W, H, matrix, row, k, col);
            cout << "New H:" << endl;
            print_matrix(H, k, col);
        }
        else
        {
            update_W(W, H, matrix, row, k, col);
            cout << "New W: " << endl;
            print_matrix(W, row, k);
        }
        counter++;
        multiply(V, W, H, row, k, col);
        cost = cost_function(matrix, V, row, col);
    }
    printf("Number of iterations: %d", counter);
}