#include <iostream>
#include <math.h>
#include "matrix_operations.h"
using namespace std;
#define e 2.71828
const double sigma = 5.0;
const double Mu = 10.0;

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
   
}
double rand(double minn, double maxx)
{
    double range = (maxx - minn);
    double div = (double)RAND_MAX / range; // 32767 is the max value of rand()
    return minn + ((double)rand() / div);
}

double exponential() // e^(-0.5*x^2)
{
    double power, x;
    x = rand(-8.0, 10.0);       // random number generator within -10.0 to 10.0
    power = ((x - sigma) / Mu); // x-sigma/Mu is the power
    double half = -0.5;
    power = pow((half * power), 2.0); // e^-0.5*power^2
    return pow(e, power);
}

double Rand_number_generator()
{
    return (0.398922804 / sigma) * exponential(); // initial = 1/root(2pi), exponantial = e^(-0.5*x^2)
}

double cost_function(double **initial_matrix, double **current, int row, int col)
{
    double cost = 0.0; // epsilon
    double sum = 0.0;

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            // square of the difference between initial and final for each index
            sum += pow((initial_matrix[i][j] - current[i][j]), 2);
        }
    }
    // root of the sum of squares epsilon
    cost = sqrt(sum);

    cout << "Cost is :" << cost << endl;

    return cost;
}
double trace(double **matrix, int index)
{
    double sum = 0.0;
    for (int i = 0; i < index; i++)
    {
        sum += matrix[i][i];
    }
    return sum;
}
void free_matrix(double **matrix, int row)
{
    for (int i = 0; i < row; i++)
    {
        free(matrix[i]);
    }
}
