#include "cpPruning.h"

cpPruning::cpPruning()
{
    CornerPermutation cornerPermutation;
    cornerPermutation.buildTransitionTable();
    vector<vector<long long>> transition_table = cornerPermutation.getTransitionTable();

    buildPruneTable(transition_table, cornerPermutation.get_state_count());
}

int cpPruning::pruning_number(Cube &cube)
{
    return prune_table[cube.getCpState()];
}
