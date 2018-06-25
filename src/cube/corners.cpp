#include "corners.h"

Corners::Corners() {
    coState = 0;
    cpState = 0;

    CornerOrientation cornerOrientation;
    cornerOrientation.buildTransitionTable();
    transition_table_orientation = cornerOrientation.getTransitionTable();

    CornerPermutation cornerPermutation;
    cornerPermutation.buildTransitionTable();
    transition_table_permutation = cornerPermutation.getTransitionTable();

    pruning_info.state_count = cornerOrientation.get_state_count() * cornerPermutation.get_state_count();
    pruning_info.maxDepthBFS = 8;
    pruning_info.maxDepth = 11;
    pruning_info.pruning_file = "cornerPruning.data";
}

void Corners::apply_move(int move) {
    coState = transition_table_orientation[coState][move];
    cpState = transition_table_permutation[cpState][move];
}

uint32_t Corners::to_index() const {
    return cpState * 2187 + coState;
}

void Corners::from_index(uint32_t state) {
    coState = state % 2187;
    cpState = state / 2187;
}

PruningInfo Corners::get_pruning_info() const {
    return pruning_info;
}
