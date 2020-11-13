#include "array.h"

array_t create_array(int n)
{
	return new int[n];
}

array_t copy_array(array_t arr, int n)
{
	array_t c = create_array(n);

	for (int i = 0; i < n; i++)
		c[i] = arr[i];

	return c;
}

void free_array(array_t* arr)
{
	delete* arr;
	*arr = nullptr;
}

void fill_array(array_t arr, int n)
{
	for (int i = 0; i < n; i++)
		cin >> arr[i];
}

array_t random_fill_array(int n)
{
	array_t arr = create_array(n);

	for (int i = 0; i < n; i++)
		arr[i] = rand() % 20 - 10;

	return arr;
}

bool cmp_array(array_t arr1, array_t arr2, int n)
{
	for (int i = 0; i < n; i++)
		if (abs(arr1[i] - arr2[i]) > EPS)
			return false;

	return true;
}

void print_array(array_t arr, int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
	cout << endl;
}