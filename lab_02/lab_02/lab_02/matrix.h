#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <memory>

#define		EPS	1e-5

using namespace std;

typedef double* arr_t;
typedef double** matrix_t;

matrix_t create_matrix(int n, int m);
void fill_matrix(matrix_t matr, int n, int m);
matrix_t random_fill_matrix(int m, int n);
bool cmp_matrix(matrix_t matr1, matrix_t matr2, int m, int q);
void free_matrix(matrix_t* matr, int n, int m);

void print_matrix(matrix_t matr, int n, int m);

arr_t create_array(int n);
void free_array(arr_t* arr);

#endif // MATRIX_H

