#ifndef CUBE_H
#define CUBE_H

#include <string>
#include "corner_orientation.h"
#include "corner_permutation.h"
#include "edge_orientation.h"
#include "edge_permutation.h"
#include "UDSlice_coord.h"


class Cube
{
private:
    vector<vector<long long>> coTransition;
    vector<vector<long long>> cpTransition;
    vector<vector<long long>> eoTransition;
    vector<vector<long long>> epTransition;
    vector<vector<long long>> UDSliceTransition;

    int coState;
    int cpState;
    int eoState;
    int epState1;
    int epState2;
    int UDSliceState;

public:
    Cube();
    Cube(string scramble);
    void apply_move(int move);
    bool is_solved();
    bool is_phase1_solved();
    int getCoState() const { return coState; }
    int getCpState() const { return cpState; }
    int getEoState() const { return eoState; }
    int getEpState1() const { return epState1; }
    int getEpState2() const { return epState2; }
    int getUDSliceState() const { return UDSliceState; }
};


#endif //CUBE_H
