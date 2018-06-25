#pragma once

#include "prune.h"

class cornerPruning : public Prune {
private:
    TransitionTable transition_table_orientation, transition_table_permutation;
public:
    cornerPruning();
    int pruning_number(Cube &cube);
private:
    void buildPruneTable();
    void pruneTreeSearch(uint32_t orient_state, uint32_t perm_state, int depth_left, int depth, int lastMove);
    bool solveable(uint32_t orient_state, uint32_t perm_state, int depth, int maxBreathDepthSearch, int lastMove);
};
