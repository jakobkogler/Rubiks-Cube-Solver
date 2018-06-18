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
    void pruneTreeSearch(long long orient_state, long long perm_state, char depth_left, char depth, int lastMove);
    bool solveable(long long orient_state, long long perm_state, char depth, char maxBreathDepthSearch, int lastMove);
};
