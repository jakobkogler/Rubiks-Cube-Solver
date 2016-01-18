#ifndef EDGEORIENTATION_H
#define EDGEORIENTATION_H

#include "group.h"

class EdgeOrientation : public Group
{
public:
    EdgeOrientation() : Group(2048, 12, "edge_orientation_prune.data") {}
    void apply_move(vector<int> & arr, int move);

private:
    void index_to_array(int index, vector<int> & arr);
    int array_to_index(vector<int> const& arr);
    void permute_array(vector<int> & arr, int idx1, int idx2, int idx3, int idx4, int increment);
};

#endif // EDGEORIENTATION_H
