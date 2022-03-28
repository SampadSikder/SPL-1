#include <bits/stdc++.h>
//#include "print_matrix.h"
const int N = 150;
using namespace std;
int max_of_two(int n1, int n2)
{
    return n1 > n2 ? n1 : n2;
}
void strassen(double **A, double **B, double **C, int n)
{
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    else
    {
        int divide = (n / 2);
        double A11[divide][divide];
    }
}
void print_matrix(double V[][N], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%lf\t", V[i][j]);
        }
        printf("\n");
    }
    cout << endl;
}
int main()
{
    freopen("in3.txt", "r", stdin);

    int row, k, i, j;
    cin >> row >> k;

    double *mat1[row];

    for (i = 0; i < row; i++)
    {
        mat1[i] = (double *)malloc(k * sizeof(double));
    }

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < k; j++)
        {
            cin >> mat1[i][j];
        }
    }

    int col;
    cin >> col;
    double *mat2[k];
    for (i = 0; i < k; i++)
    {
        mat2[i] = (double *)malloc(col * sizeof(double));
    }

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < col; j++)
        {
            cin >> mat2[i][j];
        }
    }
    // print_matrix(mat1, row, k);
    // print_matrix(mat2, k, col);

    // creating square matrices of order 2^n for all and initializing empty cells with 0
    // maximum of row,k,col
    int max_dm, temp;
    temp = max_of_two(row, k);
    max_dm = max_of_two(temp, col);
    // cout << max_dm;
    int m = (int)pow(2, max_dm);
    // cout << m;

    double *mat1_updated[m], *mat2_updated[m], *result[m];
    for (i = 0; i < m; i++)
    {
        mat1_updated[i] = (double *)malloc(m * sizeof(double));
    }
    for (i = 0; i < m; i++)
    {
        mat2_updated[i] = (double *)malloc(m * sizeof(double));
    }

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {
            cout << "hello";
            mat1_updated[i][j] = 0.0;
        }
    }

    for (i = 0; i < m; i++)
    {
        result[i] = (double *)malloc(m * sizeof(double));
    }

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < k; j++)
        {
            mat1_updated[i][j] = mat1[i][j];
        }
    }
    for (i = 0; i < k; i++)
    {
        for (j = 0; j < col; j++)
        {
            mat2_updated[i][j] = mat2[i][j];
        }
    }
    // print_matrix(mat1_updated, m, m);
    // print_matrix(mat2_updated, m, m);

    // strassen(mat1_updated, mat2_updated, result, m);
}
