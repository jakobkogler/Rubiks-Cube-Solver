#include "coPruning.h"

coPruning::coPruning()
{
    file_path = "coPruning.data";

    CornerOrientation cornerOrientation;
    cornerOrientation.buildTransitionTable();
    std::vector<std::vector<long long>> transition_table = cornerOrientation.getTransitionTable();

    buildPruneTable(transition_table, cornerOrientation.get_state_count());
}

int coPruning::pruning_number(Cube &cube)
{
    return prune_table[cube.getCoState()];
}
