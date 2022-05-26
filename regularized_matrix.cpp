#include <iostream>
#include <math.h>
#include "matrix_operations.h"
#include "print_matrix.h"
using namespace std;
void Update_U(double **X, double **W, double **U, double **V, int row, int k, int col)
{
    double *transpose_V[col];
    for (int i = 0; i < col; i++)
    {
        transpose_V[i] = (double *)malloc(k * sizeof(double));
    }
    transpose(V, transpose_V, k, col);

    double *numerator_p_1[row];
    for (int i = 0; i < row; i++)
    {
        numerator_p_1[i] = (double *)malloc(col * sizeof(double));
    }
    multiply_element_wise(numerator_p_1, W, X, row, col);
    // print_matrix(numerator_p_1, row, col);
    double *numerator[row];
    for (int i = 0; i < row; i++)
    {
        numerator[i] = (double *)malloc(k * sizeof(double));
    }
    multiply(numerator, numerator_p_1, transpose_V, row, col, k);
    // print_matrix(numerator, row, k);
    free_matrix(numerator_p_1, row);
    double *UV[row];
    for (int i = 0; i < row; i++)
    {
        UV[i] = (double *)malloc(col * sizeof(double));
    }
    multiply(UV, U, V, row, k, col);
    // print_matrix(UV, row, col);
    double *denominator_p_1[row];
    for (int i = 0; i < row; i++)
    {
        denominator_p_1[i] = (double *)malloc(col * sizeof(double));
    }
    multiply_element_wise(denominator_p_1, W, UV, row, col);
    free_matrix(UV, row);
    // print_matrix(denominator_p_1, row, col);
    double *denominator[row];
    for (int i = 0; i < row; i++)
    {
        denominator[i] = (double *)malloc(k * sizeof(double));
    }
    strassenMultiplication(denominator, denominator_p_1, transpose_V, row, col, k);
    free_matrix(denominator_p_1, row);
    // print_matrix(denominator, row, k);

    double *second_part[row];
    for (int i = 0; i < row; i++)
    {
        second_part[i] = (double *)malloc(k * sizeof(double));
    }
    divide_element_wise(second_part, numerator, denominator, row, k);
    // print_matrix(second_part, row, k);
    free_matrix(numerator, row);
    free_matrix(denominator, row);

    double *Updated_U[row];
    for (int i = 0; i < row; i++)
    {
        Updated_U[i] = (double *)malloc(k * sizeof(double));
    }
    multiply_element_wise(Updated_U, U, second_part, row, k);
    // print_matrix(Updated_U, row, k);
    copy_matrix(Updated_U, U, row, k);
    free_matrix(Updated_U, row);
}
void Update_V(double **X, double **W, double **U, double **V, int row, int k, int col)
{
    double *transpose_W[col];
    for (int i = 0; i < col; i++)
    {
        transpose_W[i] = (double *)malloc(row * sizeof(double));
    }
    transpose(W, transpose_W, row, col);
    double *transpose_X[col];
    for (int i = 0; i < col; i++)
    {
        transpose_X[i] = (double *)malloc(row * sizeof(double));
    }
    transpose(X, transpose_X, row, col);

    double *numerator_p_1[col];
    for (int i = 0; i < col; i++)
    {
        numerator_p_1[i] = (double *)malloc(row * sizeof(double));
    }
    multiply_element_wise(numerator_p_1, transpose_W, transpose_X, col, row);
    free_matrix(transpose_X, col);
    // print_matrix(numerator_p_1, col, row);
    double *numerator[col];
    for (int i = 0; i < col; i++)
    {
        numerator[i] = (double *)malloc(k * sizeof(double));
    }
    multiply(numerator, numerator_p_1, U, col, row, k);
    free_matrix(numerator_p_1, col);
    // print_matrix(numerator, col, k);
    double *transpose_V[col];
    for (int i = 0; i < col; i++)
    {
        transpose_V[i] = (double *)malloc(k * sizeof(double));
    }
    transpose(V, transpose_V, k, col);
    double *transpose_U[k];
    for (int i = 0; i < k; i++)
    {
        transpose_U[i] = (double *)malloc(row * sizeof(double));
    }
    transpose(U, transpose_U, row, k);
    // print_matrix(transpose_V, col, k);
    // print_matrix(transpose_U, k, row);
    double *VUT[col];
    for (int i = 0; i < col; i++)
    {
        VUT[i] = (double *)malloc(row * sizeof(double));
    }
    multiply(VUT, transpose_V, transpose_U, col, k, row);
    // print_matrix(VUT, col, row);
    free_matrix(transpose_U, k);

    double *denominator_p_1[col];
    for (int i = 0; i < col; i++)
    {
        denominator_p_1[i] = (double *)malloc(row * sizeof(double));
    }
    multiply_element_wise(denominator_p_1, transpose_W, VUT, col, row);
    free_matrix(VUT, col);
    // print_matrix(denominator_p_1, col, row);
    double *denominator[col];
    for (int i = 0; i < col; i++)
    {
        denominator[i] = (double *)malloc(k * sizeof(double));
    }
    strassenMultiplication(denominator, denominator_p_1, U, col, row, k);
    free_matrix(denominator_p_1, col);
    // print_matrix(denominator, col, k);

    double *second_part[col];
    for (int i = 0; i < col; i++)
    {
        second_part[i] = (double *)malloc(k * sizeof(double));
    }
    divide_element_wise(second_part, numerator, denominator, col, k);
    free_matrix(numerator, col);
    free_matrix(denominator, col);
    // print_matrix(second_part, col, k);
    double *Updated_VTranspose[col];
    for (int i = 0; i < col; i++)
    {
        Updated_VTranspose[i] = (double *)malloc(k * sizeof(double));
    }
    multiply_element_wise(Updated_VTranspose, transpose_V, second_part, col, k);
    // print_matrix(Updated_VTranspose, col, k);
    double *Updated_V[k];
    for (int i = 0; i < k; i++)
    {
        Updated_V[i] = (double *)malloc(col * sizeof(double));
    }
    transpose(Updated_VTranspose, Updated_V, col, k);
    // print_matrix(Updated_V, k, col);
    copy_matrix(Updated_V, V, k, col);
    free_matrix(Updated_V, k);
}
void regularizedMatrix()
{
    freopen("wnmf2.txt", "r", stdin);
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
    cout << "Enter user defined Lambda value: (Between 0 and 1)" << endl;
    double lambda;
    cin >> lambda;
    // adding standard epsilon value to weighted matrix
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (matrix[i][j] == -1)
            {
                matrix[i][j] = lambda;
            }
        }
    }
    normalize(matrix, row, col);
    int k;
    printf("Enter the dimension:\n");
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
    // Update_U(matrix, weighted_matrix, W, H, row, k, col);
    // Update_V(matrix, weighted_matrix, W, H, row, k, col);
    // WNMF
    //
    //
    // cost function
    int counter = 1;
    printf("Initial cost: ");
    strassenMultiplication(V, W, H, row, k, col);
    double cost = cost_function(matrix, V, row, col);
    double starting_cost = cost;
    double prev_cost = 0.0;
    while (cost > 0.05)
    {

        if ((counter % 2) != 0)
        {
            Update_U(matrix, weighted_matrix, W, H, row, k, col);
            cout << "New H" << endl;
        }
        else
        {
            Update_V(matrix, weighted_matrix, W, H, row, k, col);
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
    freopen("result2.txt", "w", stdout);
    printf("The beginning cost was: %lf\n", starting_cost);
    printf("Total number of iterations before arriving at result: %d\n", counter);
    printf("Final results:\n ");
    printf("The main matrix:\n ");
    print_matrix(matrix, row, col);
    printf("The W matrix:\n ");
    print_matrix(W, row, k);
    printf("The H matrix:\n ");
    print_matrix(H, k, col);
}
