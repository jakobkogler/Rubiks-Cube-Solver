#include "corner_permutation.h"
#include "indexing.h"


void CornerPermutation::index_to_array(int index, vector<int> & arr)
{
    Indexing::index_to_permutation(index, arr);
}

void CornerPermutation::apply_move(vector<int> & arr, int move)
{
    if (move == 0)
    {
        permute_array(arr, 0, 3, 2, 1); // U
    }
    else if (move == 1)
    {
        permute_array(arr, 4, 5, 6, 7); // D
    }
    else if (move == 2)
    {
        permute_array(arr, 1, 2, 6, 5); // R
    }
    else if (move == 3)
    {
        permute_array(arr, 0, 4, 7, 3); // L
    }
    else if (move == 4)
    {
        permute_array(arr, 2, 3, 7, 6); // F
    }
    else if (move == 5)
    {
        permute_array(arr, 0, 1, 5, 4); // F
    }
}

int CornerPermutation::array_to_index(vector<int> const& arr)
{
    return Indexing::permutation_to_index(arr);
}

void CornerPermutation::permute_array(vector<int> & arr, int idx1, int idx2, int idx3, int idx4)
{
    int tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = arr[idx3];
    arr[idx3] = arr[idx4];
    arr[idx4] = tmp;
}
