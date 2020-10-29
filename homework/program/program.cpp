#include <iostream>

#include "array.h"

using namespace std;

int* create_digit(int n)
{
	int* arr = create_array(n);
	int elem = 1;

	for (int i = 0; i < n; i++, elem *= 10)
		arr[i] = elem;

	return arr;
}

int count_rank(int num)
{
	int count = 0;

	while (num > 0)
	{
		count++;
		num /= 10;
	}

	return count;
}

int find_rank_max(array_t arr, int n)
{
	int max_elem = arr[0], elem;

	for (int i = 1; i < n; i++)
	{
		elem = arr[i];
		if (elem > max_elem)
			max_elem = elem;
	}

	return count_rank(max_elem);
}

int get_digit(int num, int i, int* digit)
{
	num %= digit[i + 1];
	num /= digit[i];

	return num;
}

void lsd_sort(array_t& arr, int n)
{
	int count, temp, d;
	int rank = find_rank_max(arr, n);
	int* degree_10 = create_digit(rank + 1);
	int num_fig[10];
	array_t temp_res = create_array(n), temp_copy;

	for (int i = 0; i < rank; i++)							// 1
	{
		for (int j = 0; j < 10; j++)						// 2
			num_fig[j] = 0;									// 3

		for (int j = 0; j < n; j++)							// 4
		{
			temp = get_digit(arr[j], i, degree_10);			// 5
			num_fig[temp]++;								// 6
		}

		count = 0;											// 7

		for (int j = 0; j < 10; j++)						// 8
		{
			temp = num_fig[j];								// 9
			num_fig[j] = count;								// 10
			count += temp;									// 11
		}

		for (int j = 0; j < n; j++)							// 12
		{
			d = get_digit(arr[j], i, degree_10);			// 13
			temp_res[num_fig[d]] = arr[j];					// 14
			num_fig[d]++;									// 15
		}

		temp_copy = arr;									// 16
		arr = temp_res;										// 17
		temp_res = temp_copy;								// 18
	}

	free_array(&degree_10);
	free_array(&temp_res);
}


int main()
{
	cout << endl << "---Sorting array A[N]---" << endl;
	cout << "Input N: ";
	int n;
	cin >> n;

	array_t arr = create_array(n);
	cout << endl;

	cout << "Input array A: " << endl;
	fill_array(arr, n);
	cout << endl;

	lsd_sort(arr, n);

	cout << "Result: " << endl;
	print_array(arr, n);

	free_array(&arr);
}
