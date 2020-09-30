#include "tests.h"


bool mult_cmp(matrix_t a, matrix_t b, int m, int n, int q)
{
	matrix_t c1 = standart_mult(a, b, m, n, q);
	matrix_t c2 = winograd_mult(a, b, m, n, q);

	bool res = cmp_matrix(c1, c2, m, q);

	free_matrix(&c1, m, q);
	free_matrix(&c2, m, q);

	return res;
}

// Матрицы размером 1х1
void test_size_1_1()
{
	int n = 1;

	matrix_t a = create_matrix(n, n);
	matrix_t b = create_matrix(n, n);

	a[0][0] = 15;
	b[0][0] = -7;

	if (!mult_cmp(a, b, n, n, n))
	{
		cout << endl << __FUNCTION__ << " FAILED" << endl;
		free_matrix(&a, n, n);
		free_matrix(&b, n, n);
		return;
	}

	free_matrix(&a, n, n);
	free_matrix(&b, n, n);

	cout << endl << __FUNCTION__ << " OK" << endl;
}

// Квадратные матрицы
void test_square_matr()
{
	int n[] = { 2, 6, 10 };

	for (int i = 0; i < sizeof(n); i++)
	{
		matrix_t a = create_matrix(n[i], n[i]);
		matrix_t b = create_matrix(n[i], n[i]);

		random_fill_matrix(a, n[i], n[i]);
		random_fill_matrix(b, n[i], n[i]);

		if (!mult_cmp(a, b, n[i], n[i], n[i]))
		{
			cout << endl << __FUNCTION__ << " FAILED" << endl;
			free_matrix(&a, n[i], n[i]);
			free_matrix(&b, n[i], n[i]);
			return;
		}

		free_matrix(&a, n[i], n[i]);
		free_matrix(&b, n[i], n[i]);

		cout << endl << __FUNCTION__ << " OK" << endl;
	}
}

void run_tests()
{
	test_size_1_1();
	test_square_matr();
}