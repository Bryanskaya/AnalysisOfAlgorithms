#include "matrix.h"

matrix_t create_matrix(int n, int m)
{
	matrix_t matr = new double* [n];

	for (int i = 0; i < n; i++)
		matr[i] = new double[m];

	return matr;
}

void fill_matrix(matrix_t matr, int n, int m)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> matr[i][j];
}

bool cmp_matrix(matrix_t matr1, matrix_t matr2, int m, int q)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < q; j++)
			if (fabs(matr1[i][j] - matr2[i][j]) > EPS)
				return false;
	return true;
}

void free_matrix(matrix_t* matr, int n, int m)
{
	for (int i = 0; i < n; i++)
		delete (*matr)[i];

	delete (*matr);
}

void print_matrix(matrix_t matr, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << matr[i][j] << ' ';
		cout << endl;
	}
}


arr_t create_array(int n)
{
	return new double[n];
}

void free_array(arr_t* arr)
{
	delete arr;
}