#pragma once
const int N = 100;
void multiply(double V[][N], double m1[][N], double m2[][N], int m, int k, int n);
void copy_matrix(double from[][N], double to[][N], int row, int col);
void transpose(double input_matrix[][N], double transpose_matrix[][N], int row, int col);
void normalize(double matrix[][N], int row, int col);
void cofactor_matrix(double matrix[][N], double sub_matrix[][N], int row, int col, int n);
double det_calculator(double D[][N], int r);
void adjoint_matrix(double matrix[][N], double adj_matrix[][N], int n);
void inverse_function(double matrix[][N], double inverse_matrix[][N], int row, int col);