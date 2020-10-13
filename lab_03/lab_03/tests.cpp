#include "tests.h"


double PCFreq = 0.0;
__int64 CounterStart = 0;


bool sort_cmp(array_t a, int n)
{
	bool res = true;
	void(*func_arr[])(array_t&, int) = { bubble_sort, insert_sort, lsd_sort };

	array_t c = copy_array(a, n);
	sort(c, c + n);

	for (int i = 0; i < 3 && res; i++)
	{
		array_t temp_arr = copy_array(a, n);

		(*func_arr[i])(temp_arr, n);

		res = cmp_array(c, temp_arr, n);

		free_array(&temp_arr);
	}

	free_array(&c);

	return res;
}

// Размер массива равен 1
void test_size_1()
{
	int n = 1;

	for (int i = 0; i < 3; i++)
	{
		array_t a = random_fill_array(n);

		if (!sort_cmp(a, n))
		{
			cout << endl << __FUNCTION__ << " FAILED" << endl;
			free_array(&a);
			return;
		}

		free_array(&a);
	}

	cout << endl << __FUNCTION__ << " OK" << endl;
}

// Произвольные массивы различный длин
void test_std()
{
	int n[] = { 3, 5, 8, 10, 12 };

	for (int i = 0; i < sizeof(n)/sizeof(n[0]); i++)
	{
		array_t a = random_fill_array(n[i]);

		if (!sort_cmp(a, n[i]))
		{
			cout << endl << __FUNCTION__ << " FAILED" << endl;
			free_array(&a);
			return;
		}

		free_array(&a);
	}

	cout << endl << __FUNCTION__ << " OK" << endl;
}

// Уже отсортированные по неубыванию массивы
void test_sorted()
{
	int n = 30;

	array_t a = random_fill_array(n);

	sort(a, a + n);

	if (!sort_cmp(a, n))
	{
		cout << endl << __FUNCTION__ << " FAILED" << endl;
		free_array(&a);
		return;
	}

	free_array(&a);

	cout << endl << __FUNCTION__ << " OK" << endl;
}

// Уже отсортированные по невозрастанию массивы
void test_reverse_sorted()
{
	int n = 30;

	array_t a = random_fill_array(n);

	sort(a, a + n);
	reverse(a, a + n);

	if (!sort_cmp(a, n))
	{
		cout << endl << __FUNCTION__ << " FAILED" << endl;
		free_array(&a);
		return;
	}

	free_array(&a);

	cout << endl << __FUNCTION__ << " OK" << endl;
}

// Массив одинаковых элементов
void test_same_elements()
{
	int n = 30;
	array_t a = create_array(n);

	for (int i = 0; i < n; i++)
		a[i] = 102;

	if (!sort_cmp(a, n))
	{
		cout << endl << __FUNCTION__ << " FAILED" << endl;
		free_array(&a);
		return;
	}

	free_array(&a);

	cout << endl << __FUNCTION__ << " OK" << endl;
}

void run_tests()
{
	test_size_1();
	test_std();
	test_sorted();
	test_reverse_sorted();
	test_same_elements();
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


void test_time(void(*f)(array_t&, int), int n)
{
	array_t a = random_fill_array(n);

	int num = 0;
	start_measuring();

	while (get_measured() < 3 * 1000)
	{
		f(a, n);
		num++;
	}

	double t = get_measured() / 1000;
	cout << "Выполнено " << num << " операций за " << t << " секунд" << endl;
	cout << "Время: " << t / num << endl;

	free_array(&a);
}