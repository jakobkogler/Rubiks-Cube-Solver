#include "indexing.h"

int Indexing::permutation_to_index(vector<int> const& arr)
{
	int n = arr.size();
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

void Indexing::index_to_permutation(int index, vector<int> & arr)
{
	int n = arr.size();
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

int Indexing::orientation_to_index_dependent(vector<int> const& arr, int orientation_cnt)
{
	int n = arr.size();
	int index = 0;
	for (int i = 0; i < n - 1; i++)
	{
		index = index * orientation_cnt + arr[i];
	}
	return index;
}

void Indexing::index_to_orientation_dependent(int index, vector<int> & arr, int orientation_cnt)
{
	int n = arr.size();
	arr[n - 1] = 0;
	for (int i = n - 2; i >= 0; i--)
	{
		arr[i] = index % orientation_cnt;
		arr[n - 1] -= arr[i];
		if (arr[n - 1] < 0)
		{
			arr[n - 1] += orientation_cnt;
		}
		index /= orientation_cnt;
	}
}
