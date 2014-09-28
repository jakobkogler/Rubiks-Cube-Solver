#ifndef CORNERORIENTATION_H
#define CORNERORIENTATION_H

#include "group.h"

class CornerOrientation : public Group
{
public:
	CornerOrientation() : Group(2187, 8) {}

private:
	void index_to_array(int index, vector<int> & arr);
	void apply_move(vector<int> & arr, int move);
	int array_to_index(vector<int> const& arr);
	void permute_array(vector<int> & arr, int idx1, int idx2, int idx3, int idx4, int increment1, int increment2);
};

#endif // CORNERORIENTATION_H
