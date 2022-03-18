#pragma once
const int N = 150;
void multiply(double **V, double **m1, double **m2, int m, int k, int n);
void divide_element_wise(double **V, double **m1, double **m2, int m, int n);
void multiply_element_wise(double **V, double **m1, double **m2, int m, int n);
void copy_matrix(double **from, double **to, int row, int col);
void transpose(double **input_matrix, double **transpose_matrix, int row, int col);
void normalize(double **matrix, int row, int col);
void cofactor_matrix(double matrix[][N], double sub_matrix[][N], int row, int col, int n);
double det_calculator(double D[][N], int r);
void adjoint_matrix(double matrix[][N], double adj_matrix[][N], int n);
void inverse_function(double matrix[][N], double inverse_matrix[][N], int row, int col);