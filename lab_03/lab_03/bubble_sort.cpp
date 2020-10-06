#include "bubble_sort.h"

#pragma optimize("", off)

void bubble_sort(array_t& arr, int n)
{
	double temp;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - 1 - i; j++)
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
}

#pragma optimize("", on)