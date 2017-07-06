#ifndef UDSLICE_COORD_H
#define UDSLICE_COORD_H

#include "group.h"

class UDSlice_Coord : public Group
{
public:
    UDSlice_Coord() : Group(495, 4) {}
    void apply_move(vector<int> & arr, int move);
    int array_to_index(vector<int> const& arr);

private:
    void index_to_array(int index, vector<int> & arr);
};

#endif // UDSLICE_COORD_H
