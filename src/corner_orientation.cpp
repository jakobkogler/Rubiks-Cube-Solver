#include "corner_orientation.h"
#include "indexing.h"


void CornerOrientation::index_to_array(int index, vector<int> & arr)
{
	Indexing::index_to_orientation_dependent(index, arr, 3);
}

void CornerOrientation::do_apply_move(vector<int> & arr, int move)
{
	if (move == 0)
	{
		permute_array(arr, 0, 3, 2, 1, 0, 0); // U
	}
	else if (move == 1)
	{
		permute_array(arr, 4, 5, 6, 7, 0, 0); // D
	}
	else if (move == 2)
	{
		permute_array(arr, 1, 2, 6, 5, 2, 1); // R
	}
	else if (move == 3)
	{
		permute_array(arr, 0, 4, 7, 3, 1, 2); // L
	}
	else if (move == 4)
	{
		permute_array(arr, 2, 3, 7, 6, 2, 1); // F
	}
	else if (move == 5)
	{
		permute_array(arr, 0, 1, 5, 4, 2, 1); // F
	}
}

int CornerOrientation::array_to_index(vector<int> const& arr)
{
	return Indexing::orientation_to_index_dependent(arr, 3);
}

void CornerOrientation::permute_array(vector<int> & arr, int idx1, int idx2, int idx3, int idx4, int increment1, int increment2)
{
	int tmp = arr[idx1];
	arr[idx1] = (arr[idx2] + increment1) % 3;
	arr[idx2] = (arr[idx3] + increment2) % 3;
	arr[idx3] = (arr[idx4] + increment1) % 3;
	arr[idx4] = (tmp + increment2) % 3;
}
