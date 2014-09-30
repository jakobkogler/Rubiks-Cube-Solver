#ifndef EDGEPERMUTATION_H
#define EDGEPERMUTATION_H

#include "group.h"

class EdgePermutation : public Group
{
public:
	EdgePermutation() : Group(665280, 6) {}
	int array_to_index(vector<int> const& arr);

private:
	void index_to_array(int index, vector<int> & arr);
	void apply_move(vector<int> & arr, int move);
};

#endif // EDGEPERMUTATION_H
