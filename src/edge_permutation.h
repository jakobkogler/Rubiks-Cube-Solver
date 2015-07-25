#ifndef EDGEPERMUTATION_H
#define EDGEPERMUTATION_H

#include "group.h"

class EdgePermutation : public Group
{
private:
	vector<char> prune_table2;

public:
	EdgePermutation() : Group(665280, 6, "edge_permutation_prune.data") {}
	int array_to_index(vector<int> const& arr);
	//void buildPruneTable2();
	//vector<char> getPruneTable2(){ return prune_table2; }

private:
	void index_to_array(int index, vector<int> & arr);
	void apply_move(vector<int> & arr, int move);
};

#endif // EDGEPERMUTATION_H
