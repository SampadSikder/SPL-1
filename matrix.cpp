#include <iostream>
#include <bits/stdc++.h>
#include "matrix_operations.h"
using namespace std;

void multiply(double **V, double **m1, double **m2, int m, int k, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            V[i][j] = 0;
            for (int x = 0; x < k; x++)
            {
                V[i][j] += m1[i][x] * m2[x][j];
            }
        }
    }
}
void multiply_element_wise(double **V, double **m1, double **m2, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            V[i][j] = m1[i][j] * m2[i][j];
        }
    }
}
void divide_element_wise(double **V, double **m1, double **m2, int m, int n) // divide element wise
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            V[i][j] = m1[i][j] / m2[i][j];
        }
    }
}

void copy_matrix(double **from, double **to, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            to[i][j] = from[i][j];
        }
    }
}
/*void transpose(double input[][N], int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (i == j)
                continue;
            else
            {
                double temp = input[i][j];
                input[i][j] = input[j][i];
                input[j][i] = temp;
            }
        }
    }
    // print_matrix(input, col, row);
}*/
void normalize(double **matrix, int row, int col)
{
    double avg, sd, var = 0.0, sum = 0.0;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            sum += matrix[i][j];
        }
    }
    avg = sum / (row * col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            var += pow((matrix[i][j] - avg), 2);
        }
    }
    var = var / ((row * col) - 1);
    sd = sqrt(var);

    // cout << "SD: " << sd << endl;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = matrix[i][j] / sd;
        }
    }
}
void transpose(double **input_matrix, double **transpose_matrix, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            transpose_matrix[j][i] = input_matrix[i][j];
        }
    }
    // print_matrix(transpose_matrix, col, row);
}