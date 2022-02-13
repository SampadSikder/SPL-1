#include <iostream>
#include <math.h>
using namespace std;
#define e 2.71828
const double sigma = 5.0;
const double Mu = 10.0;
const double initial = 0.398922804 / sigma;

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
    cout << x << endl;
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

void print_two_matrix(double m1[][100], double m2[][100], int m, int k, int n)
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
void print_matrix(double V[][100], int m, int n)
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
void print_matrix_using_pointer(double **V, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << V[i][j] << " ";
        }
        cout << endl;
    }
}

double **multiply(double m1[][100], double m2[][100], int m, int k, int n)
{
    double V[100][100];

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
    // dynamic memory allocation to return 2d array
    double **V_ret = new double *[m]; // m is the number of rows
    for (int i = 0; i < m; i++)
    {
        V_ret[i] = new double[n]; // each row has n columns
        for (int j = 0; j < n; j++)
        {
            V_ret[i][j] = V[i][j];
        }
    }

    return V_ret;
}

void cost_function(double initial_matrix[][100], double **current, int row, int col)
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

    cout << cost << endl;
}

int main()
{
    double matrix[100][100] = {};
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
    // Generating two matrices using user input dimension and random number generator
    //  Dimension of broken matrix
    printf("Enter dimension: ");
    cin >> k;

    printf("Matrix broken and initialized using Gaussian dist: ");
    double m_part1[100][100] = {}, m_part2[100][100] = {}; // broken down in m*k and k*n matrix

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

    double **V = multiply(m_part1, m_part2, row, k, col);

    printf("V= \n");

    print_matrix_using_pointer(V, row, col);

    // cost function
    cost_function(matrix, V, row, col);
}