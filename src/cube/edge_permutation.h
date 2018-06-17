#pragma once

#include "group.h"

class EdgePermutation : public Group
{
public:
    EdgePermutation() : Group(665280, 6) {}
    void apply_move(std::vector<int> & arr, int move);
    int array_to_index(std::vector<int> const& arr);

private:
    void index_to_array(int index, std::vector<int> & arr);
};
