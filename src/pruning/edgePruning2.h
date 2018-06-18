#pragma once

#include "prune.h"
#include <initializer_list>

class edgePruning2 : public Prune {
public:
    edgePruning2(int pieces_cnt);
    int pruning_number(Cube &cube);
    int visited;
private:
    void buildPruneTable();
    void pruneTreeSearch(Cube & cube, char depth_left, char depth, int lastMove);
    bool solveable(Cube & cube, char depth, char maxBreathDepthSearch, int lastMove);

    const int pieces_cnt;
};
