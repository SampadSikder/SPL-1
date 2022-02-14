#include <iostream>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;
#define e 2.71828
const double sigma = 5.0;
const double Mu = 10.0;
const double initial = 0.398922804 / sigma;
const int N = 200;

double randfrom(double minn, double maxx)
{
    double range = (maxx - minn);
    double div = (double)RAND_MAX / range; // 32767 is the max value of rand()
    return minn + ((double)rand() / div);
}

double exponential() // e^(-0.5*x^2)
{
    double power, x;
    // power = (-0.5 * pow(randfrom(-1, 1), 2)); // randfrom(-1,1) is a random number between 0 and 1
    x = randfrom(-9.0, 10.0);
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

void print_two_matrix(double m1[][N], double m2[][N], int m, int k, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < k; j++)
        {
            cout << m1[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << m2[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// when we print a declared 2d array
void print_matrix(double V[][N], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << V[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// When we print a dynamically allocated 2d array
/*void print_matrix_using_pointer(double V[][N], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << V[i][j] << " ";
        }
        cout << endl;
    }
}*/

void normalize(double matrix[][N], int row, int col)
{
    double avg, sd, var = 0, sum = 0;

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
    sd = sqrt(var);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matrix[i][j] = matrix[i][j] / sd;
        }
    }
}

void multiply(double V[][N], double m1[][N], double m2[][N], int m, int k, int n)
{
    // double V[N][N];

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
void transpose(double W[][N], double transpose_matrix[][N], int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            transpose_matrix[j][i] = W[i][j];
        }
    }
    print_matrix(transpose_matrix, col, row);
}

/*void cofactor_matrix(double matrix[][N], double sub_matrix[][N], int row, int col, int n)
{ // je row ar je col bad dibo
    int i = 0, j = 0;

    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (r != row || q != col)
            {
                sub_matrix[i][j] = matrix[r][c];
                j++;
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}*/

/*double det_calculator(double D[][N], int r)
{
    if (r == 1)
    {
        return D[0][0];
    }
    if (r == 2)
    {
        return (D[0][0] * D[1][1]) - (D[0][1] * D[1][0]);
    }
    int sub_matrix[N][N] = {0};
    double det = 0;
    double sign = 1;
    for (int i = 0; i < r; i++)
    {
        cofactor_matrix(D, sub_matrix, 0, i, r);
        det += sign * D[0][i] * det_calculator(sub_matrix, r - 1);
        sign = -sign;
    }
}*/
/*void inverse_function(double matrix[][N],double inverse_matrix[][N],int row, int col){
    double A_transpose_A[N][N]={0}, transpose_A[N][N]={0};

    transpose(matrix, transpose_A, row, col);//transpose_A te ashtese transpose matrix

    multiply(A_transpose_A, matrix, transpose_A, row, col, row);//matrix ke gun dilam transpose_A diye ar value stored at A_transpose_A

    double det_A=0;

    double D[][N]={0};

    det_calculator(A_transpose_A,row);





}*/

/*void update_H(double H[][N], double W[][N], double V[][N], int row, int k, int col)
{
    double transpose_matrix[N][N] = {0},inverse_matrix[N][N] = {0};

    transpose(W, transpose_matrix, k, col);

    inverse_function(W,inverse_matrix,row,col);
}*/

int main()
{
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
    double m_part1[N][N] = {}, m_part2[N][N] = {}; // broken down in m*k and k*n matrix

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < k; j++)
        {
            m_part1[i][j] = Rand_number(); // send to random number generator
        }
    }

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < col; j++)
        {
            m_part2[i][j] = Rand_number(); // send to random number generator
        }
    }

    printf("Print broken down matrices:\n");
    print_two_matrix(m_part1, m_part2, row, k, col);
    // multiplication
    double V[N][N] = {0};
    multiply(V, m_part1, m_part2, row, k, col);

    printf("V= \n");

    print_matrix(V, row, col);

    // print_matrix_using_pointer(V, row, col);
    // counting number of iterations
    int counter = 0;
    // cost function
    double cost = cost_function(V, matrix, row, col);
    // update_H(m_part1, m_part2, V, row, k, col);
    /*while (cost_function(V, matrix, row, col) > 0.05)
    {
        if (counter % 2 == 0)
        {
            counter++;
            update_H(m_part1, m_part2, V, row, k, col);
            break;
        }
    }*/
}