#include "ep2Pruning.h"

ep2Pruning::ep2Pruning()
{
    file_path = "ep2Pruning.data";

    EdgePermutation edgePermutation;
    edgePermutation.buildTransitionTable();
    std::vector<std::vector<long long>> transition_table = edgePermutation.getTransitionTable();

    buildPruneTable(transition_table, edgePermutation.get_state_count(), 366288);
}

int ep2Pruning::pruning_number(Cube &cube)
{
    return prune_table[cube.getEpState2()];
}
