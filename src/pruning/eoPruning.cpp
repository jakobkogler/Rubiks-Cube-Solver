#include "eoPruning.h"

eoPruning::eoPruning()
{
    EdgeOrientation edgeOrientation;
    edgeOrientation.buildTransitionTable();
    vector<vector<long long>> transition_table = edgeOrientation.getTransitionTable();

    buildPruneTable(transition_table, edgeOrientation.get_state_count());
}

int eoPruning::pruning_number(Cube &cube)
{
    return prune_table[cube.getEoState()];
}
