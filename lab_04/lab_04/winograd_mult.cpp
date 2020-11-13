#include "winograd_mult.h"

matrix_t winograd_mult(matrix_t a, matrix_t b, int m, int n, int q)
{
	arr_t mulV = create_array(q);
	int temp = n - 1;
	double mulH, buf;

	matrix_t c = create_matrix(m, q);

	for (int i = 0; i < q; i++)
	{
		buf = 0;
		for (int k = 1; k < n; k += 2)
			buf += b[k][i] * b[k - 1][i];
		mulV[i] = buf;
	}

	for (int i = 0; i < m; i++)
	{
		mulH = 0;
		for (int k = 1; k < n; k += 2)
			mulH += a[i][k] * a[i][k - 1];

		for (int j = 0; j < q; j++)
		{
			buf = -(mulH + mulV[j]);
			for (int k = 1, t = 0; k < n; k += 2, t += 2)
				buf += (a[i][k] + b[t][j]) * (a[i][t] + b[k][j]);
			c[i][j] = buf;

			if (n % 2)
				c[i][j] += a[i][temp] * b[temp][j];
		}
	}

	free_array(&mulV);

	return c;
}
