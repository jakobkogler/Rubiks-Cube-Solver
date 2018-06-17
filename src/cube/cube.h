#pragma once

#include <string>
#include "corner_orientation.h"
#include "corner_permutation.h"
#include "edge_orientation.h"
#include "edge_permutation.h"
#include "edges.h"


class Cube
{
private:
    std::vector<std::vector<long long>> coTransition;
    std::vector<std::vector<long long>> cpTransition;
    std::vector<std::vector<long long>> eoTransition;
    std::vector<std::vector<long long>> epTransition;

    int coState;
    int cpState;
    int eoState;
    int epState1;
    int epState2;

public:
    Cube();
    Cube(std::string scramble);
    void apply_move(int move);
    bool is_solved();
    int getCoState() const { return coState; }
    int getCpState() const { return cpState; }
    int getEoState() const { return eoState; }
    int getEpState1() const { return epState1; }
    int getEpState2() const { return epState2; }

    Edges edges;
};
