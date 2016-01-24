#ifndef CUBE_H
#define CUBE_H

#include <string>
#include "corner_orientation.h"
#include "corner_permutation.h"
#include "edge_orientation.h"
#include "edge_permutation.h"


class Cube
{
private:
    vector<vector<long long>> coTransition;
    vector<vector<long long>> cpTransition;
    vector<vector<long long>> eoTransition;
    vector<vector<long long>> epTransition;

    int coState;
    int cpState;
    int eoState;
    int epState1;
    int epState2;

public:
    Cube();
    Cube(string scramble);
    void apply_move(int move);
    bool is_solved();
};


#endif //CUBE_H
