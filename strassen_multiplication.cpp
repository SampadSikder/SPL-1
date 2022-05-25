#include <iostream>
#include <math.h>
#include "print_matrix.h"
#include "matrix_operations.h"
// const int N = 150;
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

void MatrixSubtract(double **A, double **B, double **result, int n)
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
        // cout << "Recursive calls" << endl;
        int divide = (n / 2);
        double *A11[divide], *A12[divide], *A21[divide], *A22[divide];
        double *B11[divide], *B12[divide], *B21[divide], *B22[divide];
        double *C11[divide], *C12[divide], *C21[divide], *C22[divide];
        double *AResult[divide], *BResult[divide];
        double *P1[divide], *P2[divide], *P3[divide], *P4[divide], *P5[divide], *P6[divide], *P7[divide];

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
            AResult[i] = (double *)malloc(divide * sizeof(double));
            BResult[i] = (double *)malloc(divide * sizeof(double));
            C11[i] = (double *)malloc(divide * sizeof(double));
            C12[i] = (double *)malloc(divide * sizeof(double));
            C21[i] = (double *)malloc(divide * sizeof(double));
            C22[i] = (double *)malloc(divide * sizeof(double));
            P1[i] = (double *)malloc(divide * sizeof(double));
            P2[i] = (double *)malloc(divide * sizeof(double));
            P3[i] = (double *)malloc(divide * sizeof(double));
            P4[i] = (double *)malloc(divide * sizeof(double));
            P5[i] = (double *)malloc(divide * sizeof(double));
            P6[i] = (double *)malloc(divide * sizeof(double));
            P7[i] = (double *)malloc(divide * sizeof(double));
        }

        for (int i = 0; i < divide; i++)
        {
            for (int j = 0; j < divide; j++)
            {
                // cout << "assigning" << endl;
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
        MatrixAdd(A11, A22, AResult, divide);   // a11 + a22
        MatrixAdd(B11, B22, BResult, divide);   // b11 + b22
        strassen(AResult, BResult, P1, divide); // p1 = (a11+a22) * (b11+b22)

        MatrixAdd(A21, A22, AResult, divide); // a21 + a22
        strassen(AResult, B11, P2, divide);   // p2 = (a21+a22) * (b11)

        MatrixSubtract(B12, B22, BResult, divide); // b12 - b22
        strassen(A11, BResult, P3, divide);        // p3 = (a11) * (b12 - b22)

        MatrixSubtract(B21, B11, BResult, divide); // b21 - b11
        strassen(A22, BResult, P4, divide);        // p4 = (a22) * (b21 - b11)

        MatrixAdd(A11, A12, AResult, divide); // a11 + a12
        strassen(AResult, B22, P5, divide);   // p5 = (a11+a12) * (b22)

        MatrixSubtract(A21, A11, AResult, divide); // a21 - a11
        MatrixAdd(B11, B12, BResult, divide);      // b11 + b12
        strassen(AResult, BResult, P6, divide);    // p6 = (a21-a11) * (b11+b12)

        MatrixSubtract(A12, A22, AResult, divide); // a12 - a22
        MatrixAdd(B21, B22, BResult, divide);      // b21 + b22
        strassen(AResult, BResult, P7, divide);    // p7 = (a12-a22) * (b21+b22)

        // calculating c21, c21, c11 e c22:

        MatrixAdd(P3, P5, C12, divide); // c12 = p3 + p5
        MatrixAdd(P2, P4, C21, divide); // c21 = p2 + p4

        MatrixAdd(P1, P4, AResult, divide);       // p1 + p4
        MatrixAdd(AResult, P7, BResult, divide);  // p1 + p4 + p7
        MatrixSubtract(BResult, P5, C11, divide); // c11 = p1 + p4 - p5 + p7

        MatrixAdd(P1, P3, AResult, divide);       // p1 + p3
        MatrixAdd(AResult, P6, BResult, divide);  // p1 + p3 + p6
        MatrixSubtract(BResult, P2, C22, divide); // c22 = p1 + p3 - p2 + p6

        // Grouping the results obtained in a single matrice:

        for (int i = 0; i < divide; i++)
        {
            for (int j = 0; j < divide; j++)
            {
                C[i][j] = C11[i][j];
                C[i][j + divide] = C12[i][j];
                C[i + divide][j] = C21[i][j];
                C[i + divide][j + divide] = C22[i][j];
            }
        }
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
void strassenMultiplication(double **V, double **m1, double **m2, int row, int k, int col)
{
    // print_matrix(mat1, row, k);
    // print_matrix(mat2, k, col);

    // creating square matrices of order 2^n for all and initializing empty cells with 0
    // maximum of row,k,col
    int max_dm, temp, i, j;
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
            // cout << "hello";
            mat1_updated[i][j] = 0.0;
        }
    }

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < m; j++)
        {
            // cout << "hello";
            mat2_updated[i][j] = 0.0;
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
            mat1_updated[i][j] = m1[i][j];
        }
    }
    for (i = 0; i < k; i++)
    {
        for (j = 0; j < col; j++)
        {
            mat2_updated[i][j] = m2[i][j];
        }
    }
    // print_matrix(mat1_updated, m, m);
    // print_matrix(mat2_updated, m, m);

    strassen(mat1_updated, mat2_updated, result, m);

    copy_matrix(result, V, row, col);
}
