#include "winograd_mult.h"

#pragma optimize("", off)

matrix_t winograd_opt_mult(matrix_t a, matrix_t b, int m, int n, int q)
{
	arr_t mulH = create_array(m);
	arr_t mulV = create_array(q);
	double buf;
	
	matrix_t c = create_matrix(m, q);

	for (int i = 0; i < m; i++)
	{
		buf = 0;
		for (int k = 1; k < n; k += 2)
			buf += a[i][k] * a[i][k - 1];
		mulH[i] = buf;
	}

	for (int i = 0; i < q; i++)
	{
		buf = 0;
		for (int k = 1; k < n; k += 2)
			buf += b[k][i] * b[k - 1][i];
		mulV[i] = buf;
	}

	int temp = n - 1;

	for (int i = 0; i < m; i++)
		for (int j = 0; j < q; j++)
		{
			buf = -(mulH[i] + mulV[j]);
			for (int k = 1, t = 0; k < n; k += 2, t +=2)
				buf += (a[i][k] + b[t][j]) * (a[i][t] + b[k][j]);
			c[i][j] = buf;

			if (n % 2)
				c[i][j] += a[i][temp] * b[temp][j];
		}


	free_array(&mulH);
	free_array(&mulV);
	
	return c;
}

matrix_t winograd_mult(matrix_t a, matrix_t b, int m, int n, int q)
{
	arr_t mulH = create_array(m);
	arr_t mulV = create_array(q);
	matrix_t c = create_matrix(m, q);

	for (int i = 0; i < m; i++)
	{
		mulH[i] = 0;
		for (int k = 0; k < n / 2; k++)
			mulH[i] = mulH[i] + a[i][2 * k] * a[i][2 * k + 1];
	}

	for (int i = 0; i < q; i++)
	{
		mulV[i] = 0;
		for (int k = 0; k < n / 2; k++)
			mulV[i] = mulV[i] + b[2 * k][i] * b[2 * k + 1][i];
	}

	for (int i = 0; i < m; i++)
		for (int j = 0; j < q; j++)
		{
			c[i][j] = -mulH[i] - mulV[j];
			for (int k = 0; k < n / 2; k++)
				c[i][j] = c[i][j] + (a[i][2 * k] + b[2 * k + 1][j]) * (a[i][2 * k + 1] + b[2 * k][j]);
		}

	if (n % 2)
		for (int i = 0; i < m; i++)
			for (int j = 0; j < q; j++)
				c[i][j] = c[i][j] + a[i][n - 1] * b[n - 1][j];

	return c;
}

#pragma optimize("", on)