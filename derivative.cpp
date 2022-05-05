#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include "print_matrix.h"
#include "matrix_operations.h"
#include "matrix_factorizations.h"
using namespace std;

void derivative()
{
    int row, col;
    printf("Enter number of rows and column:");
    cin >> row >> col;

    double *matrix[N];
    for (int i = 0; i < row; i++)
    {
        matrix[i] = (double *)malloc(col * sizeof(double));
    }
    printf("Enter the matrix:\n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> matrix[i][j];
        }
    }
    int k;
    printf("Enter factorization rank:");
    cin >> k;

    double *W[N], *H[N];
    for (int i = 0; i < row; i++)
    {
        W[i] = (double *)malloc(k * sizeof(double));
    }
    for (int i = 0; i < k; i++)
    {
        H[i] = (double *)malloc(col * sizeof(double));
    }
    gradientDescent(matrix, W, H, row, k, col);

    printf("Derivative of input matrix with respect to \n1. A matrix\t2. B Matrix\n");

    int choice;

    cin >> choice;
    if (choice == 1)
    {
        double *I[row];
        for (int i = 0; i < row; i++)
        {
            I[i] = (double *)malloc(k * sizeof(double));
        }
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < k; j++)
            {
                if (i == j)
                {
                    I[i][j] = 1.0;
                }
                else
                {
                    I[i][j] = 0.0;
                }
            }
        }
        double *derivative[row];
        for (int i = 0; i < row; i++)
        {
            derivative[i] = (double *)malloc(col * sizeof(double));
        }
        multiply(derivative, I, H, row, k, col);
        printf("The derivative matrix:\n");
        print_matrix(derivative, row, col);
    }
    else if (choice == 2)
    {
        double *I[col];
        for (int i = 0; i < col; i++)
        {
            I[i] = (double *)malloc(k * sizeof(double));
        }
        for (int i = 0; i < col; i++)
        {
            for (int j = 0; j < k; j++)
            {
                if (i == j)
                {
                    I[i][j] = 1.0;
                }
                else
                {
                    I[i][j] = 0.0;
                }
            }
        }
        double *transpose_W[k];
        for (int i = 0; i < k; i++)
        {
            transpose_W[i] = (double *)malloc(row * sizeof(double));
        }
        double *transpose_derivative[col];
        for (int i = 0; i < col; i++)
        {
            transpose_derivative[i] = (double *)malloc(row * sizeof(double));
        }
        transpose(W, transpose_W, row, k);
        multiply(transpose_derivative, I, transpose_W, col, k, row);
        double *derivative[row];
        for (int i = 0; i < row; i++)
        {
            derivative[i] = (double *)malloc(col * sizeof(double));
        }
        transpose(transpose_derivative, derivative, col, row);
        printf("The derivative matrix:\n");
        print_matrix(derivative, row, col);
    }
}