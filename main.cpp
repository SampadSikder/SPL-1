#include <iostream>
#include <math.h>
using namespace std;

#define e 2.71828
#define initial 0.398922804

double randfrom(double minn, double maxx)
{
    srand(100); // seed of rand
    double range = (maxx - minn);
    double div = 32767 / range; // 32767 is the max value of rand()
    return minn + (rand() / div);
}

double exponential() // e^(-0.5*x^2)
{
    double power;
    power = (-0.5 * pow(randfrom(-1, 1), 2)); // randfrom(0,1) is a random number between 0 and 1
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
}

void multiply(double m1[][100], double m2[][100], int m, int k, int n)
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
    print_matrix(V, m, n);
}

int main()
{
    int matrix[100][100] = {};
    int row, col, i, j, k;

    // Taking input
    cin >> row >> col; // m*n matrix
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
            cin >> matrix[i][j];
    }
    // Generating two matrices using user input dimension and random number generator
    //  Dimension of broken matrix
    cin >> k;

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
    print_two_matrix(m_part1, m_part2, row, k, col);
    // multiplication
    multiply(m_part1, m_part2, row, k, col);
}