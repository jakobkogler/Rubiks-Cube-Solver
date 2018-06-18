#pragma once

#include "prune.h"
#include <initializer_list>

class edgePruning : public Prune {
public:
    edgePruning(int pieces_cnt);
    int pruning_number(Cube &cube);
    int visited;
private:
    void buildPruneTable();
    void pruneTreeSearch(Cube & cube, char depth_left, char depth, int lastMove);
    bool solveable(Cube & cube, char depth, char maxBreathDepthSearch, int lastMove);

    const int pieces_cnt;
};
