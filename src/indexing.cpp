#include "indexing.h"

int Indexing::permutation_to_index(int *arr, int n)
{
	int index = 0;
	for (int i = 0; i < n; i++)
	{
		index *= n - i;
		for (int j = i; j < n; j++)
		{
			if (arr[i] > arr[j])
			{
				index += 1;
			}
		}
	}
	return index;
}

void Indexing::index_to_permutation(int index, int *arr, int n)
{
	arr[n - 1] = 0;
	for (int i = n - 2; i >= 0; i--)
	{
		arr[i] = index % (n - i);
		index /= n - i;
		for (int j = i + 1; j < n; j++)
		{
			if (arr[j] >= arr[i])
			{
				arr[j]++;
			}
		}
	}
}