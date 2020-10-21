#include "lsd_sort.h"

#pragma optimize("", off)

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

int analyze_arr(array_t arr, int n, int& flag)
{
	int min_elem = arr[0], max_elem = min_elem, elem;

	for (int i = 1; i < n; i++)
	{
		elem = arr[i];
		if (elem > max_elem)
			max_elem = elem;
		if (elem < min_elem)
			min_elem = elem;
	}

	if (min_elem < 0)
	{
		max_elem -= min_elem;
		flag = -min_elem;

		for (int i = 0; i < n; i++)
			arr[i] -= min_elem;
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
	int flag = 0, count, temp, d;
	int rank = analyze_arr(arr, n, flag);
	int* degree_10 = create_digit(rank + 1);
	int num_fig[10];
	array_t temp_res = create_array(n), temp_copy;

	for (int i = 0; i < rank; i++)
	{
		for (int j = 0; j < 10; j++)
			num_fig[j] = 0;

		for (int j = 0; j < n; j++)
			num_fig[get_digit(arr[j], i, degree_10)]++;
		
		count = 0;

		for (int j = 0; j < 10; j++)
		{
			temp = num_fig[j];
			num_fig[j] = count;
			count += temp;
		}

		for (int j = 0; j < n; j++)
		{
			d = get_digit(arr[j], i, degree_10);
			temp_res[num_fig[d]] = arr[j];
			num_fig[d]++;
		}

		temp_copy = arr;
		arr = temp_res;
		temp_res = temp_copy;
	}

	free_array(&degree_10);
	free_array(&temp_res);

	if (flag)
		for (int i = 0; i < n; i++)
			arr[i] -= flag;
}

#pragma optimize("", on)