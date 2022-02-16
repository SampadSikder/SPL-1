#include <iostream>
#include <bits/stdc++.h>
#include "print_matrix.h"
using namespace std;

void print_two_matrix(double m1[][N], double m2[][N], int m, int k, int n)
{

    printf("W=\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < k; j++)
        {
            printf("%lf\t", m1[i][j]);
        }
        cout << endl;
    }
    printf("H=\n");

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%lf\t", m2[i][j]);
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
            printf("%lf\t", V[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}