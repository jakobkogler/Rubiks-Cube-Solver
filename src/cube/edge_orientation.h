#ifndef EDGE_ORIENTATION_H
#define EDGE_ORIENTATION_H

#include "group.h"

class EdgeOrientation : public Group
{
public:
    EdgeOrientation() : Group(2048, 12) {}
    void apply_move(std::vector<int> & arr, int move);
    int array_to_index(std::vector<int> const& arr);

private:
    void index_to_array(int index, std::vector<int> & arr);
    void permute_array(std::vector<int> & arr, int idx1, int idx2, int idx3, int idx4, int increment);
};

#endif // EDGE_ORIENTATION_H
