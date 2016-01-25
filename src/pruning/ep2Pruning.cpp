#include "ep2Pruning.h"

ep2Pruning::ep2Pruning()
{
    EdgePermutation edgePermutation;
    edgePermutation.buildTransitionTable();
    vector<vector<long long>> transition_table = edgePermutation.getTransitionTable();

    buildPruneTable(transition_table, edgePermutation.get_state_count(), 366288);
}

int ep2Pruning::pruning_number(Cube &cube)
{
    return prune_table[cube.getEpState2()];
}
