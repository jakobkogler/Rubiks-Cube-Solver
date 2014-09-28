#include "edge_orientation.h"
#include "indexing.h"


void EdgeOrientation::index_to_array(int index, vector<int> & arr)
{
	Indexing::index_to_orientation_dependent(index, arr, 2);
}

void EdgeOrientation::apply_move(vector<int> & arr, int move)
{
	if (move == 0)
	{
		permute_array(arr, 0, 3, 2, 1, 0); // U
	}
	else if (move == 1)
	{
		permute_array(arr, 8, 9, 10, 11, 0); // D
	}
	else if (move == 2)
	{
		permute_array(arr, 1, 6, 9, 5, 0); // R
	}
	else if (move == 3)
	{
		permute_array(arr, 3, 4, 11, 7, 0); // L
	}
	else if (move == 4)
	{
		permute_array(arr, 2, 7, 10, 6, 1); // F
	}
	else if (move == 5)
	{
		permute_array(arr, 0, 5, 8, 4, 1); // F
	}
}

int EdgeOrientation::array_to_index(vector<int> const& arr)
{
	return Indexing::orientation_to_index_dependent(arr, 2);
}

void EdgeOrientation::permute_array(vector<int> & arr, int idx1, int idx2, int idx3, int idx4, int increment)
{
	int tmp = arr[idx1];
	arr[idx1] = (arr[idx2] + increment) % 2;
	arr[idx2] = (arr[idx3] + increment) % 2;
	arr[idx3] = (arr[idx4] + increment) % 2;
	arr[idx4] = (tmp + increment) % 2;
}
