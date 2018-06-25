#include "cornerPruning.h"

cornerPruning::cornerPruning()
{
    file_path = "cornerPruning.data";

    buildPruneTable();
}

int cornerPruning::pruning_number(Cube &cube)
{
    return prune_table.get(cube.getCpState() * 2187u + cube.getCoState());
}

void cornerPruning::buildPruneTable()
{
    CornerOrientation cornerOrientation;
    CornerPermutation cornerPermutation;

    cornerOrientation.buildTransitionTable();
    transition_table_orientation = cornerOrientation.getTransitionTable();

    cornerPermutation.buildTransitionTable();
    transition_table_permutation = cornerPermutation.getTransitionTable();

    uint32_t state_count = cornerOrientation.get_state_count() * cornerPermutation.get_state_count();

    prune_table = Nibble32(state_count, 11u);
    if (!prune_table.read(file_path)) {
        int maxBreathDepthSearch = 8;

        for (char depth = 0; depth <= maxBreathDepthSearch; depth++) {
            pruneTreeSearch(0, 0, depth, depth, -1);
        }


        for (uint32_t i = 0u; i < state_count; i++) {
            if (prune_table.get(i) < 11)
                continue;

            //Only the position smaller than 11, since 11 is max
            for (int depth = maxBreathDepthSearch + 1; depth < 11; depth++) {
                if (solveable(i % 2187, i / 2187, depth, maxBreathDepthSearch, -1)) {
                    prune_table.set(i, depth);
                    break;
                }
            }
        }

        prune_table.store(file_path);
    }
}

void cornerPruning::pruneTreeSearch(uint32_t orient_state, uint32_t perm_state, int depth_left, int depth, int lastMove)
{
    uint32_t state = perm_state * 2187 + orient_state;
    if (depth_left == 0)
    {
        if (prune_table.get(state) > depth)
        {
            prune_table.set(state, depth);
        }
    }
    else
    {
        if (prune_table.get(state) == depth - depth_left)
        {
            for (int move = 0; move < 6; move++)
            {
                if (move == lastMove)
                    continue;
                if ((lastMove & 1) == 1 && move == lastMove - 1)
                    continue;

                for (int j = 0; j < 3; j++)
                {
                    orient_state = transition_table_orientation[orient_state][move];
                    perm_state = transition_table_permutation[perm_state][move];
                    pruneTreeSearch(orient_state, perm_state, depth_left - 1, depth, move);
                }
                orient_state = transition_table_orientation[orient_state][move];
                perm_state = transition_table_permutation[perm_state][move];
            }
        }
    }
}

bool cornerPruning::solveable(uint32_t orient_state, uint32_t perm_state, int depth, int maxBreathDepthSearch, int lastMove)
{
    uint32_t state = perm_state * 2187u + orient_state;
    if (prune_table.get(state) == depth)
    {
        return true;
    }
    else if (depth <= maxBreathDepthSearch)
    {
        return false;
    }
    else
    {
        for (int move = 0; move < 6; move++)
        {
            if (move == lastMove)
                continue;
            if ((lastMove & 1) == 1 && move == lastMove - 1)
                continue;

            for (int j = 0; j < 3; j++)
            {
                orient_state = transition_table_orientation[orient_state][move];
                perm_state = transition_table_permutation[perm_state][move];
                if (solveable(orient_state, perm_state, depth - 1, maxBreathDepthSearch, move))
                {
                    return true;
                }
            }
            orient_state = transition_table_orientation[orient_state][move];
            perm_state = transition_table_permutation[perm_state][move];
        }

        return false;
    }
}
