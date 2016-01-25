#include "epPruning.h"

epPruning::epPruning()
{
    EdgePermutation edgePermutation;
    edgePermutation.buildTransitionTable();
    vector<vector<long long>> transition_table = edgePermutation.getTransitionTable();

    buildPruneTable(transition_table, edgePermutation.get_state_count());
}

int epPruning::pruning_number(Cube &cube)
{
    return prune_table[cube.getEpState1()];
}
