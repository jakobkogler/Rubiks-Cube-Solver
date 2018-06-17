#pragma once

#include "group.h"

class CornerOrientation : public Group
{
public:
    CornerOrientation() : Group(2187, 8) {}
    void apply_move(std::vector<int> & arr, int move);
    int array_to_index(std::vector<int> const& arr);

private:
    void index_to_array(int index, std::vector<int> & arr);
    void permute_array(std::vector<int> & arr, int idx1, int idx2, int idx3, int idx4, int increment1, int increment2);
};
