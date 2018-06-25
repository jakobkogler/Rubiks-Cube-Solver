#pragma once

#include <string>
#include "corner_orientation.h"
#include "corner_permutation.h"
#include "edges.h"


class Cube
{
private:
    TransitionTable coTransition;
    TransitionTable cpTransition;

    int coState;
    int cpState;

public:
    Cube(int edgePruningSize);
    Cube(std::string scramble, int edgePruningSize);
    void apply_move(int move);
    bool is_solved();
    int getCoState() const { return coState; }
    int getCpState() const { return cpState; }

    Edges edges;
    Edges edges2;
};
