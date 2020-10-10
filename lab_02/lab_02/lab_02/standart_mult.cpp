#include "standart_mult.h"

#pragma optimize("", off)

matrix_t standart_mult(matrix_t a, matrix_t b, int m, int n, int q)
{
	matrix_t c = create_matrix(m, q);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < q; j++)
		{
			c[i][j] = 0;
			for (int k = 0; k < n; k++)
				c[i][j] += a[i][k] * b[k][j];
		}

	return c;
}

#pragma optimize("", on)