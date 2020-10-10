#include "insert_sort.h"

#pragma optimize("", off)

void insert_sort(array_t& arr, int n)
{
	double temp;
	int k;

	for (int i = 1; i < n; i++)
	{
		temp = arr[i];
		k = 0;

		while (arr[k] < temp)
			k += 1;

		for (int j = i; j > k; j--)
			arr[j] = arr[j - 1];
		arr[k] = temp;
	}
}
#pragma optimize("", on)