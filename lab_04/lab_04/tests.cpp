#include "tests.h"


double PCFreq = 0.0;
__int64 CounterStart = 0;


bool mult_cmp(matrix_t a, matrix_t b, int m, int n, int q, int num_thread = 5)
{
	matrix_t c1 = winograd_mult(a, b, m, n, q);
	matrix_t c2 = parall_winograd_mult_1(a, b, m, n, q, num_thread);

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

// Один поток
void test_one_thread()
{
	int m[] = { 2, 6, 10 };
	int n[] = { 1, 4, 7 };
	int q[] = { 3, 4, 8 };
	int num_thread = 1;


	for (int i = 0; i < sizeof(n) / sizeof(n[0]); i++)
	{
		matrix_t a = random_fill_matrix(m[i], n[i]);
		matrix_t b = random_fill_matrix(n[i], q[i]);

		if (!mult_cmp(a, b, m[i], n[i], q[i], num_thread))
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

// Потоков меньше, чем значения M, N, Q
void test_less_mnq()
{
	int m[] = { 4, 8, 10 };
	int n[] = { 3, 5, 12 };
	int q[] = { 3, 6, 8 };
	int num_thread[] = { 2, 4, 2 };


	for (int i = 0; i < sizeof(n) / sizeof(n[0]); i++)
	{
		matrix_t a = random_fill_matrix(m[i], n[i]);
		matrix_t b = random_fill_matrix(n[i], q[i]);

		if (!mult_cmp(a, b, m[i], n[i], q[i], num_thread[i]))
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

// Потоков больше, чем значения M, N, Q
void test_more_mnq()
{
	int m[] = { 4, 8, 10 };
	int n[] = { 3, 5, 12 };
	int q[] = { 3, 6, 8 };
	int num_thread[] = { 7, 10, 15 };


	for (int i = 0; i < sizeof(n) / sizeof(n[0]); i++)
	{
		matrix_t a = random_fill_matrix(m[i], n[i]);
		matrix_t b = random_fill_matrix(n[i], q[i]);

		if (!mult_cmp(a, b, m[i], n[i], q[i], num_thread[i]))
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

// Умножение одних и тех же матриц на разном числе потоков
void test_dif_num_threads()
{
	int m = 20, n = 17, q = 23;
	int num_thread[] = { 1, 2, 5, 8, 10, 14, 16, 19, 20, 24, 26, 30 };

	for (int i = 0; i < sizeof(num_thread) / sizeof(num_thread[0]); i++)
	{
		matrix_t a = random_fill_matrix(m, n);
		matrix_t b = random_fill_matrix(n, q);

		if (!mult_cmp(a, b, m, n, q, num_thread[i]))
		{
			cout << endl << __FUNCTION__ << " FAILED" << endl;
			free_matrix(&a, m, n);
			free_matrix(&b, n, q);
			return;
		}
		free_matrix(&a, m, n);
		free_matrix(&b, n, q);

		cout << endl << __FUNCTION__ << " OK" << endl;
	}
}


void run_tests()
{
	test_size_1_1();
	test_one_thread();
	test_less_mnq();
	test_more_mnq();
	test_dif_num_threads();
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

// Замеры процессорного времени
void test_time_parall(matrix_t(*f)(matrix_t, matrix_t, int, int, int, int), int n, int num_threads)
{
	matrix_t a = random_fill_matrix(n, n);
	matrix_t b = random_fill_matrix(n, n);
	matrix_t c;

	int num = 0;
	start_measuring();

	while (get_measured() < 3 * 1000)
	{
		c = f(a, b, n, n, n, num_threads);
		free_matrix(&c, n, n);
		num++;
	}

	double t = get_measured() / 1000;
	cout << "Выполнено " << num << " операций за " << t << " секунд" << endl;
	cout << "Время: " << t / num << endl;

	free_matrix(&a, n, n);
	free_matrix(&b, n, n);
}

void test_time_cons(matrix_t(*f)(matrix_t, matrix_t, int, int, int), int n)
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