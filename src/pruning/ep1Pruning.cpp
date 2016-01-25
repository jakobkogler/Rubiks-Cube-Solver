#include "ep1Pruning.h"

ep1Pruning::ep1Pruning()
{
    file_path = "ep1Pruning.data";

    EdgePermutation edgePermutation;
    edgePermutation.buildTransitionTable();
    vector<vector<long long>> transition_table = edgePermutation.getTransitionTable();

    buildPruneTable(transition_table, edgePermutation.get_state_count());
}

int ep1Pruning::pruning_number(Cube &cube)
{
    return prune_table[cube.getEpState1()];
}
