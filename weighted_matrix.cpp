#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include "print_matrix.h"
#include "matrix_operations.h"

using namespace std;

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
}