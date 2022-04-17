#include <bits/stdc++.h>
#include "matrix_operations.h"
#include "print_matrix.h"
#include "my_library.h"
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
    double *denominator_p_1[row];
    for (int i = 0; i < row; i++)
    {
        denominator_p_1[i] = (double *)malloc(col * sizeof(double));
    }
    multiply_element_wise(denominator_p_1, UV, W, row, col);
    free_matrix(UV, row);
    // print_matrix(denominator_p_1, row, col);
    double *denominator[row];
    for (int i = 0; i < row; i++)
    {
        denominator[i] = (double *)malloc(k * sizeof(double));
    }
    multiply(denominator, denominator_p_1, transpose_V, row, col, k);
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
}
int main()
{
    freopen("in4.txt", "r", stdin);
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
    cout << "Enter user defined Lambda value: ";
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

    // WNMF
    Update_U(matrix, weighted_matrix, W, H, row, k, col);
}
