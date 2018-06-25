#pragma once

#include <string>
#include "corners.h"
#include "edges.h"


class Cube
{
public:
    Cube(int edgePruningSize);
    Cube(std::string scramble, int edgePruningSize);
    void apply_move(int move);
    bool is_solved();

    Corners corners;
    Edges edges;
    Edges edges2;
};
