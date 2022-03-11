#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include "print_matrix.h"
#include "matrix_operations.h"

using namespace std;

int main()
{
    double matrix[N][N];
    int row, col;

    cout << "Enter number of rows and columns" << endl;
    cin >> row >> col;

    cout << "Enter the matrix" << endl;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cin >> matrix[i][j];
        }
    }
    double weighted_matrix[N][N];

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