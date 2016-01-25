#ifndef EDGE_PERMUTATION_H
#define EDGE_PERMUTATION_H

#include "group.h"

class EdgePermutation : public Group
{
public:
    EdgePermutation() : Group(665280, 6) {}
    void apply_move(vector<int> & arr, int move);
    int array_to_index(vector<int> const& arr);

private:
    void index_to_array(int index, vector<int> & arr);
};

#endif // EDGE_PERMUTATION_H
