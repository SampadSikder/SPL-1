#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include "print_matrix.h"
#include "matrix_operations.h"
using namespace std;

void update_H(double **W, double **H, double **V, int row, int k, int col)
{
    double *transpose_W[N];
    for (int i = 0; i < k; i++)
    {
        transpose_W[i] = (double *)malloc(row * sizeof(double));
    }
    // cout << "WT=";

    transpose(W, transpose_W, row, k);

    // print_matrix(transpose_W, k, row);

    double *WH[N];
    for (int i = 0; i < row; i++)
    {
        WH[i] = (double *)malloc(col * sizeof(double));
    }
    multiply(WH, W, H, row, k, col);

    // print_matrix(WH, row, col);

    double *V_by_WH[N];
    // V/WH
    for (int i = 0; i < row; i++)
    {
        V_by_WH[i] = (double *)malloc(col * sizeof(double));
    }
    divide_element_wise(V_by_WH, V, WH, row, col);
    // cout << "V by WH";
    //  print_matrix(V_by_WH, row, col);
    //   Clearing WH
    for (int i = 0; i < row; i++)
    {
        free(WH[i]);
    }
    // WT*(V/WH)
    double *numerator[N];
    for (int i = 0; i < k; i++)
    {
        numerator[i] = (double *)malloc(col * sizeof(double));
    }
    multiply(numerator, transpose_W, V_by_WH, k, row, col);

    // Row summation of WT i.e column summation of W
    double *row_one_matrix[N]; // Matrix of 1 with 1 column
    for (int i = 0; i < row; i++)
    {
        row_one_matrix[i] = (double *)malloc(sizeof(double));
        row_one_matrix[i][0] = 1.0;
    }
    double *denominator[N]; // matrix
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
    double *new_H[N];
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
    double *updated_H[N];

    for (int i = 0; i < k; i++)
    {
        updated_H[i] = (double *)malloc(col * sizeof(double));
    }
    multiply_element_wise(updated_H, H, new_H, k, col);
    // print_matrix(updated_H, k, col);
    copy_matrix(updated_H, H, row, col);
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

    print_matrix(matrix, row, col);
    // Generating two matrices using user input dimension and random number generator
    //  Dimension of broken matrix
    printf("Enter dimension: ");
    cin >> k;

    printf("Matrix broken and initialized using Gaussian dist: ");
    double *W[N], *H[N]; // broken down in m*k and k*n matrix

    for (int i = 0; i < row; i++)
        W[i] = (double *)malloc(k * sizeof(double));
    for (int i = 0; i < k; i++)
        H[i] = (double *)malloc(col * sizeof(double));

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < k; j++)
        {
            W[i][j] = Rand_number(); // send to random number generator
        }
    }

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < col; j++)
        {
            H[i][j] = Rand_number(); // send to random number generator
        }
    }

    printf("Print broken down matrices:\n");
    print_two_matrix(W, H, row, k, col);
    // multiplication
    double *V[N];
    for (int i = 0; i < row; i++)
        V[i] = (double *)malloc(col * sizeof(double));
    multiply(V, W, H, row, k, col);

    int counter = 1;
    printf("Initial cost: ");
    // cost function
    double cost = cost_function(matrix, V, row, col);

    // kulback-leibler divergence
    update_H(W, H, matrix, row, k, col);
    /*while (cost > 0.05)
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
    }*/
}