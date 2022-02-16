#include <iostream>
#include <bits/stdc++.h>
#include "matrix_operations.h"
#include "print_matrix.h"
using namespace std;
void cofactor_matrix(double matrix[][N], double sub_matrix[][N], int row, int col, int n)
{ // je row ar je col bad dibo
    int i = 0, j = 0;

    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (r != row && c != col)
            {
                sub_matrix[i][j] = matrix[r][c];
                j++;
                if (j == n - 1) // when col == j we go to next row
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
double det_calculator(double D[][N], int r)
{
    if (r == 1)
    {
        return D[0][0];
    }
    if (r == 2)
    {
        return (D[0][0] * D[1][1]) - (D[0][1] * D[1][0]);
    }
    double sub_matrix[N][N] = {0};
    double det = 0;
    double sign = 1;
    for (int i = 0; i < r; i++)
    {
        cofactor_matrix(D, sub_matrix, 0, i, r);
        det += sign * D[0][i] * det_calculator(sub_matrix, r - 1);
        sign = -sign;
    }
    return det;
}
void adjoint_matrix(double matrix[][N], double adj_matrix[][N], int n)
{
    if (n == 1)
    {
        matrix[0][0] = 1;
    }
    else
    {
        double sub_matrix[N][N] = {};
        int sign = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cofactor_matrix(matrix, sub_matrix, i, j, n);
                if ((i + j) % 2 == 0)
                {
                    sign = 1;
                }
                else
                    sign = -1;
                adj_matrix[j][i] += sign * det_calculator(sub_matrix, n - 1);
            }
        }
    }
}
void inverse_function(double matrix[][N], double inverse_matrix[][N], int row, int col) // inverse using moore penrose method (AAT)^-1 * AT
{

    double A_transpose_A[N][N] = {0}, transpose_A[N][N] = {0}, A_transpose_adj[N][N] = {0};

    // copy_matrix(matrix, transpose_A, row, col);

    // cout << "Copy matrix: " << endl;

    // print_matrix(transpose_A, row, col);

    transpose(matrix, transpose_A, row, col); // transpose_A te ashtese transpose matrix

    // cout << "Transpose: " << endl;

    // print_matrix(transpose_A, col, row);

    multiply(A_transpose_A, transpose_A, matrix, col, row, col); // matrix ke gun dilam transpose_A diye ar value stored at A_transpose_A

    // double D[N][N] = {0};

    double det = det_calculator(A_transpose_A, col); // row col should be equal
    cout << "Determinant is: " << det << endl;

    adjoint_matrix(A_transpose_A, A_transpose_adj, col);
    double AT_A_inverse[N][N] = {};
    // inverse
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < col; j++)
        {
            AT_A_inverse[i][j] = A_transpose_adj[i][j] / det; // AAT value
        }
    }
    multiply(inverse_matrix, AT_A_inverse, transpose_A, col, col, row);
}