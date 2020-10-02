#include "tests.h"

double PCFreq = 0.0;
__int64 CounterStart = 0;

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

	for (int i = 0; i < sizeof(n) / sizeof(n[0]); i++)
	{
		matrix_t a = random_fill_matrix(n[i], n[i]);
		matrix_t b = random_fill_matrix(n[i], n[i]);

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

// Прямоугольные матрицы
void test_rectangulat_matr()
{
	int m[] = { 2, 6, 10 };
	int n[] = { 1, 4, 7 };
	int q[] = { 3, 4, 8 };


	for (int i = 0; i < sizeof(n) / sizeof(n[0]); i++)
	{
		matrix_t a = random_fill_matrix(m[i], n[i]);
		matrix_t b = random_fill_matrix(n[i], q[i]);

		if (!mult_cmp(a, b, m[i], n[i], q[i]))
		{
			cout << endl << __FUNCTION__ << " FAILED" << endl;
			free_matrix(&a, m[i], n[i]);
			free_matrix(&b, n[i], q[i]);
			return;
		}
		free_matrix(&a, m[i], n[i]);
		free_matrix(&b, n[i], q[i]);

		cout << endl << __FUNCTION__ << " OK" << endl;
	}
}

// Матрицы с чётным размером
void test_even_size()
{
	int m[] = { 2, 4 };
	int n[] = { 6, 2 };
	int q[] = { 2, 8 };


	for (int i = 0; i < sizeof(n) / sizeof(n[0]); i++)
	{
		matrix_t a = random_fill_matrix(m[i], n[i]);
		matrix_t b = random_fill_matrix(n[i], q[i]);

		if (!mult_cmp(a, b, m[i], n[i], q[i]))
		{
			cout << endl << __FUNCTION__ << " FAILED" << endl;
			free_matrix(&a, m[i], n[i]);
			free_matrix(&b, n[i], q[i]);
			return;
		}

		free_matrix(&a, m[i], n[i]);
		free_matrix(&b, n[i], q[i]);

		cout << endl << __FUNCTION__ << " OK" << endl;
	}
}

// Матрицы с нечётным размером
void test_odd_size()
{
	int m[] = { 3, 3 };
	int n[] = { 3, 1 };
	int q[] = { 5, 7 };


	for (int i = 0; i < sizeof(n) / sizeof(n[0]); i++)
	{
		matrix_t a = random_fill_matrix(m[i], n[i]);
		matrix_t b = random_fill_matrix(n[i], q[i]);

		if (!mult_cmp(a, b, m[i], n[i], q[i]))
		{
			cout << endl << __FUNCTION__ << " FAILED" << endl;
			free_matrix(&a, m[i], n[i]);
			free_matrix(&b, n[i], q[i]);
			return;
		}
	
		free_matrix(&a, m[i], n[i]);
		free_matrix(&b, n[i], q[i]);

		cout << endl << __FUNCTION__ << " OK" << endl;
	}
}

void run_tests()
{
	test_size_1_1();
	test_square_matr();
	test_rectangulat_matr();
	test_even_size();
	test_odd_size();
}

void start_measuring()
{
	LARGE_INTEGER li;
	QueryPerformanceFrequency(&li);

	PCFreq = double(li.QuadPart) / 1000;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double get_measured()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	
	return double(li.QuadPart - CounterStart) / PCFreq;
}

void test_time(matrix_t(*f)(matrix_t, matrix_t, int, int, int), int n)
{
	matrix_t a = random_fill_matrix(n, n);
	matrix_t b = random_fill_matrix(n, n);
	matrix_t c;

	int num = 0;
	start_measuring();

	while (get_measured() < 3 * 1000)
	{
		c = f(a, b, n, n, n);
		free_matrix(&c, n, n);
		num++;
	}

	double t = get_measured() / 1000;
	cout << "Выполнено " << num << " операций за " << t << " секунд" << endl;
	cout << "Время: " << t / num << endl;

	free_matrix(&a, n, n);
	free_matrix(&b, n, n);
}