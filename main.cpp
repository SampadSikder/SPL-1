#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
#include "print_matrix.h"
#include "matrix_operations.h"
using namespace std;
#define e 2.71828
const double sigma = 5.0;
const double Mu = 10.0;
const double initial = 0.398922804 / sigma;

double rand(double minn, double maxx)
{
    double range = (maxx - minn);
    double div = (double)RAND_MAX / range; // 32767 is the max value of rand()
    return minn + ((double)rand() / div);
}

double exponential() // e^(-0.5*x^2)
{
    double power, x;
    // power = (-0.5 * pow(randfrom(-1, 1), 2)); // randfrom(-1,1) is a random number between 0 and 1
    x = rand(-8.0, 10.0); // random number generator within -10.0 to 10.0
    // cout << x << endl;
    power = ((x - sigma) / Mu); // x-sigma/Mu is the power
    // cout << power << endl;
    double half = -0.5;
    power = pow((half * power), 2.0); // e^-0.5*power^2
    // cout << power << endl;
    return pow(e, power);
}

double Rand_number()
{
    return initial * exponential(); // initial = 1/root(2pi), exponantial = e^(-0.5*x^2)
}

double cost_function(double initial_matrix[][N], double current[][N], int row, int col)
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

void update_H(double W[][N], double H[][N], double V[][N], int row, int k, int col)
{
    double transpose_W[N][N], numerator[N][N];

    transpose(W, transpose_W, row, k); // WT

    multiply(numerator, transpose_W, V, k, row, col); // WT*V

    double den_part1[N][N], denominator[N][N];

    multiply(den_part1, transpose_W, W, k, row, k); // WT*W

    multiply(denominator, den_part1, H, k, k, col); //(WT*W)*H

    double updated_H[N][N]; // the term that is to be multiplied with H

    divide_element_wise(updated_H, numerator, denominator, k, col);

    double ans_H[N][N];

    multiply_element_wise(ans_H, H, updated_H, k, col);

    copy_matrix(ans_H, H, k, col);
}
void update_W(double W[][N], double H[][N], double V[][N], int row, int k, int col)
{
    double HT[N][N], numerator[N][N];

    transpose(H, HT, k, col); // HT

    multiply(numerator, V, HT, row, col, k); // V*HT

    double HHT[N][N];

    multiply(HHT, H, HT, k, col, k); // HT*H

    double denominator[N][N];

    multiply(denominator, W, HHT, row, k, k);

    double updated_W[N][N];

    divide_element_wise(updated_W, numerator, denominator, row, k);

    double ans_W[N][N];

    multiply_element_wise(ans_W, W, updated_W, row, k);

    copy_matrix(ans_W, W, row, k);
}

int main()
{
    freopen("in2.txt", "r", stdin);
    double matrix[N][N] = {};
    int row, col, i, j, k;

    printf("Enter number of rows and cols: ");
    // Taking input
    cin >> row >> col; // m*n matrix

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
    double W[N][N] = {}, H[N][N] = {}; // broken down in m*k and k*n matrix

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
    double V[N][N] = {0};
    multiply(V, W, H, row, k, col);

    printf("V= \n");

    // print_matrix(V, row, col);

    int counter = 1;
    printf("Initial cost: ");
    // cost function
    double cost = cost_function(matrix, V, row, col);

    while (cost > 0.05)
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
    }
    printf("Total number of iterations before arriving at result: %d\n", counter);
    printf("Final result: ");
    print_two_matrix(W, H, row, k, col);
}