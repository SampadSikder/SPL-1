#include <iostream>
#include <math.h>
#include "print_matrix.h"
#include "matrix_operations.h"
#include "matrix_factorizations.h"
using namespace std;

void update_H(double **W, double **H, double **V, int row, int k, int col)
{
    double *transpose_W[N], *numerator[N];

    // allocating transpose_W and numerator
    for (int i = 0; i < k; i++)
        transpose_W[i] = (double *)malloc(row * sizeof(double));

    for (int i = 0; i < k; i++)
        numerator[i] = (double *)malloc(col * sizeof(double));

    transpose(W, transpose_W, row, k); // WT

    multiply(numerator, transpose_W, V, k, row, col); // WT*V

    double *den_part1[N], *denominator[N];

    for (int i = 0; i < k; i++)
        den_part1[i] = (double *)malloc(k * sizeof(double));
    for (int i = 0; i < k; i++)
        denominator[i] = (double *)malloc(col * sizeof(double));

    multiply(den_part1, transpose_W, W, k, row, k); // WT*W

    multiply(denominator, den_part1, H, k, k, col); //(WT*W)*H

    double *updated_H[N]; // the term that is to be multiplied with H

    for (int i = 0; i < k; i++)
        updated_H[i] = (double *)malloc(col * sizeof(double));
    divide_element_wise(updated_H, numerator, denominator, k, col);

    double *ans_H[N];

    for (int i = 0; i < k; i++)
        ans_H[i] = (double *)malloc(col * sizeof(double));
    multiply_element_wise(ans_H, H, updated_H, k, col);

    copy_matrix(ans_H, H, k, col);
}
void update_W(double **W, double **H, double **V, int row, int k, int col)
{
    double *HT[N], *numerator[N];

    for (int i = 0; i < col; i++)
        HT[i] = (double *)malloc(k * sizeof(double));

    transpose(H, HT, k, col); // HT

    for (int i = 0; i < row; i++)
        numerator[i] = (double *)malloc(k * sizeof(double));

    multiply(numerator, V, HT, row, col, k); // V*HT

    double *HHT[N];

    for (int i = 0; i < k; i++)
        HHT[i] = (double *)malloc(k * sizeof(double));

    multiply(HHT, H, HT, k, col, k); // HT*H

    double *denominator[N];

    for (int i = 0; i < row; i++)
        denominator[i] = (double *)malloc(k * sizeof(double));

    multiply(denominator, W, HHT, row, k, k);

    double *updated_W[N];

    for (int i = 0; i < row; i++)
        updated_W[i] = (double *)malloc(k * sizeof(double));

    divide_element_wise(updated_W, numerator, denominator, row, k);

    double *ans_W[N];

    for (int i = 0; i < row; i++)
        ans_W[i] = (double *)malloc(k * sizeof(double));

    multiply_element_wise(ans_W, W, updated_W, row, k);

    copy_matrix(ans_W, W, row, k);
}

void gradientDescent()
{
    freopen("data.txt", "r", stdin);
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
    double *V[N];
    for (int i = 0; i < row; i++)
        V[i] = (double *)malloc(col * sizeof(double));
    multiply(V, W, H, row, k, col);

    printf("V= \n");

    // print_matrix(V, row, col);

    int counter = 1;
    printf("Initial cost: ");
    // cost function
    double cost = cost_function(matrix, V, row, col);
    double initial_cost = cost;
    double prev_cost = 0;
    printf("Updating costs:\n ");
    while (cost > 0.05)
    {

        if ((counter % 2) == 0)
        {
            update_H(W, H, matrix, row, k, col);
            cout << "New H" << endl;
        }
        else
        {
            update_W(W, H, matrix, row, k, col);
            cout << "New W" << endl;
        }
        counter++;
        multiply(V, W, H, row, k, col);
        cost = cost_function(matrix, V, row, col);
        if (fabs(prev_cost - cost) <= EPSILON)
        {
            printf("Reached relative minima\n");
            break;
        }
        else
        {
            prev_cost = cost;
        }

        // local minima reached need to stop by calculating difference with previous error
    }
    printf("Factorization done!");
    freopen("result.txt", "w", stdout);
    printf("The beginning cost was: %lf\n", initial_cost);
    printf("Total number of iterations before arriving at result: %d\n", counter);
    printf("The broken down matrix:\n ");
    print_two_matrix(W, H, row, k, col);
}
void gradientDescent(double **matrix, double **A, double **B, int row, int col, int k)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < k; j++)
        {
            A[i][j] = Rand_number_generator(); // send to random number generator
        }
    }

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < col; j++)
        {
            B[i][j] = Rand_number_generator(); // send to random number generator
        }
    }
    double *V[N];
    for (int i = 0; i < row; i++)
        V[i] = (double *)malloc(col * sizeof(double));

    int counter = 1;
    printf("Initial cost:\n");
    // cost function
    double cost = cost_function(matrix, V, row, col);
    double initial_cost = cost;
    double prev_cost = 0;
    printf("Updating costs:\n ");
    while (cost > 0.05)
    {

        if ((counter % 2) == 0)
        {
            update_H(A, B, matrix, row, k, col);
        }
        else
        {
            update_W(A, B, matrix, row, k, col);
        }
        counter++;
        multiply(V, A, B, row, k, col);
        cost = cost_function(matrix, V, row, col);
        if (fabs(prev_cost - cost) <= EPSILON)
        {
            printf("Reached relative minima\n");
            break;
        }
        else
        {
            prev_cost = cost;
        }

        // local minima reached need to stop by calculating difference with previous error
    }
    printf("Factorization done!\n");
    freopen("result.txt", "w", stdin);
    printf("The beginning cost was: %lf\n", initial_cost);
    printf("Total number of iterations before arriving at result: %d\n", counter);
    printf("Final result:\n ");
    printf("The broken down matrix:\n ");
    print_two_matrix(A, B, row, k, col);
}