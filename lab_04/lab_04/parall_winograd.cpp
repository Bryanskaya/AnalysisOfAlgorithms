#include "parall_winograd.h"

mutex set_mutex;


void process_threads_1(matrix_t& c, int start, matrix_t& a, matrix_t& b, int m, int n, int q, arr_t mulV, int step)
{
	double mulH, buf;
	int temp = n - 1;

	for (int i = start; i < m; i += step)
	{
		mulH = 0;
		for (int k = 1; k < n; k += 2)
			mulH += a[i][k] * a[i][k - 1];

		for (int j = 0; j < q; j++)
		{
			buf = -(mulH + mulV[j]);
			for (int k = 1, t = 0; k < n; k += 2, t += 2)
				buf += (a[i][k] + b[t][j]) * (a[i][t] + b[k][j]);
			
			set_mutex.lock();
			c[i][j] = buf;
			set_mutex.unlock();

			if (n % 2)
			{
				set_mutex.lock();
				c[i][j] += a[i][temp] * b[temp][j];
				set_mutex.unlock();
			}
		}
	}
}

matrix_t parall_winograd_mult_1(matrix_t a, matrix_t b, int m, int n, int q, int num_thread)
{
	arr_t mulV = create_array(q);
	double buf;

	matrix_t c = create_matrix(m, q);
	vector<thread> thread_arr;

	for (int i = 0; i < q; i++)
	{
		buf = 0;
		for (int k = 1; k < n; k += 2)
			buf += b[k][i] * b[k - 1][i];
		mulV[i] = buf;
	}

	for (int i = 0; i < num_thread; i++)
		thread_arr.push_back(thread(process_threads_1, ref(c), i, ref(a), ref(b), m, n, q, mulV, num_thread));

	for (int i = 0; i < num_thread; i++)
		thread_arr[i].join();

	free_array(&mulV);

	return c;
}



void process_threads_2(matrix_t& c, int start, matrix_t& a, matrix_t& b, int m, int n, int q, arr_t mulV, int step)
{
	double mulH, buf;
	int temp = n - 1;

	for (int i = 0; i < m; i++)
	{
		mulH = 0;
		for (int k = 1; k < n; k += 2)
			mulH += a[i][k] * a[i][k - 1];

		for (int j = start; j < q; j += step)
		{
			buf = -(mulH + mulV[j]);
			for (int k = 1, t = 0; k < n; k += 2, t += 2)
				buf += (a[i][k] + b[t][j]) * (a[i][t] + b[k][j]);

			set_mutex.lock();
			c[i][j] = buf;
			set_mutex.unlock();

			if (n % 2)
			{
				set_mutex.lock();
				c[i][j] += a[i][temp] * b[temp][j];
				set_mutex.unlock();
			}
		}
	}
}

matrix_t parall_winograd_mult_2(matrix_t a, matrix_t b, int m, int n, int q, int num_thread)
{
	arr_t mulV = create_array(q);
	double buf;

	matrix_t c = create_matrix(m, q);
	vector<thread> thread_arr;

	for (int i = 0; i < q; i++)
	{
		buf = 0;
		for (int k = 1; k < n; k += 2)
			buf += b[k][i] * b[k - 1][i];
		mulV[i] = buf;
	}

	for (int i = 0; i < num_thread; i++)
		thread_arr.push_back(thread(process_threads_2, ref(c), i, ref(a), ref(b), m, n, q, mulV, num_thread));

	for (int i = 0; i < num_thread; i++)
		thread_arr[i].join();

	free_array(&mulV);

	return c;
}