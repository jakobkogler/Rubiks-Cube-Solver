#ifndef CORNERPERMUTATION_H
#define CORNERPERMUTATION_H

#include "group.h"

class CornerPermutation : public Group
{
public:
	CornerPermutation() : Group(40320, 8, "corner_permutation_prune.data") {}
	void apply_move(vector<int> & arr, int move);

private:
	void index_to_array(int index, vector<int> & arr);
	int array_to_index(vector<int> const& arr);
	void permute_array(vector<int> & arr, int idx1, int idx2, int idx3, int idx4);
};

#endif // CORNERPERMUTATION_H
