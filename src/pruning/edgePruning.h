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
    void pruneTreeSearch(Edges & edges, int depth_left, int depth, int lastMove);
    bool solveable(Edges & edges, int depth, int maxBreathDepthSearch, int lastMove);

    int pieces_cnt;
};
