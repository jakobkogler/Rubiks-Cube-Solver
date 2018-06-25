#pragma once

#include "prune.h"

class edgePruning : public Prune {
public:
    edgePruning(int pieces_cnt);
    int pruning_number(Edges &edges);
    int pruning_number(Cube &cube) { return 0; }
    uint64_t visited;
private:
    void buildPruneTable();
    void pruneTreeSearch(Edges & edges, char depth_left, char depth, int lastMove);
    bool solveable(Edges & edges, char depth, char maxBreathDepthSearch, int lastMove);

    int pieces_cnt;
};
