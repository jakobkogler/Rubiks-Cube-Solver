#ifndef CORNER_PERMUTATION_H
#define CORNER_PERMUTATION_H

#include "group.h"

class CornerPermutation : public Group
{
public:
    CornerPermutation() : Group(40320, 8) {}
    void apply_move(std::vector<int> & arr, int move);
    int array_to_index(std::vector<int> const& arr);

private:
    void index_to_array(int index, std::vector<int> & arr);
    void permute_array(std::vector<int> & arr, int idx1, int idx2, int idx3, int idx4);
};

#endif // CORNER_PERMUTATION_H
