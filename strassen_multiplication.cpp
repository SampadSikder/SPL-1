#include <bits/stdc++.h>
//#include "print_matrix.h"
const int N = 150;
using namespace std;
int max_of_two(int n1, int n2)
{
    return n1 > n2 ? n1 : n2;
}

void MatrixAdd(double **A, double **B, double **result, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

void MatrixSubtrac(double **A, double **B, double **result, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
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
        double *A11[divide], *A12[divide], *A21[divide], *A22[divide];
        double *B11[divide], *B12[divide], *B21[divide], *B22[divide];
        double *C11[divide], *C12[divide], *C21[divide], *C22[divide];
        double *AResult[divide], *BResult[divide];
        double *P1[n], *P2[n], *P3[n], *P4[n], *P5[n], *P6[n], *P7[n];

        for (int i = 0; i < divide; i++)
        {
            A11[i] = (double *)malloc(divide * sizeof(double));
            A12[i] = (double *)malloc(divide * sizeof(double));
            A21[i] = (double *)malloc(divide * sizeof(double));
            A22[i] = (double *)malloc(divide * sizeof(double));
            B11[i] = (double *)malloc(divide * sizeof(double));
            B12[i] = (double *)malloc(divide * sizeof(double));
            B21[i] = (double *)malloc(divide * sizeof(double));
            B22[i] = (double *)malloc(divide * sizeof(double));
        }
        for (int i = 0; i < n; i++)
        {
            P1[i] = (double *)malloc(n * sizeof(double));
            P2[i] = (double *)malloc(n * sizeof(double));
            P3[i] = (double *)malloc(n * sizeof(double));
            P4[i] = (double *)malloc(n * sizeof(double));
            P5[i] = (double *)malloc(n * sizeof(double));
        }
        for (int i = 0; i < divide; i++)
        {
            for (int j = 0; j < divide; j++)
            {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + divide];
                A21[i][j] = A[i + divide][j];
                A22[i][j] = A[i + divide][j + divide];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + divide];
                B21[i][j] = B[i + divide][j];
                B22[i][j] = B[i + divide][j + divide];
            }
        }
        MatrixAdd(A11, A22, AResult, divide);
        MatrixAdd(B11, B22, BResult, divide);   // b11 + b22
        strassen(AResult, BResult, P1, divide); // p1 = (a11+a22) * (b11+b22)

        MatrixAdd(A21, A22, AResult, divide);
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
