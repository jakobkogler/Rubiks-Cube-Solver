#include "cornerPruning.h"
#include "fileio.h"

cornerPruning::cornerPruning()
{
    file_path = "cornerPruning.data";

    buildPruneTable();
}

int cornerPruning::pruning_number(Cube &cube)
{
    return prune_table[(long long)cube.getCpState() * 2187 + cube.getCoState()];
}

void cornerPruning::buildPruneTable()
{
    CornerOrientation cornerOrientation;
    CornerPermutation cornerPermutation;

    cornerOrientation.buildTransitionTable();
    transition_table_orientation = cornerOrientation.getTransitionTable();

    cornerPermutation.buildTransitionTable();
    transition_table_permutation = cornerPermutation.getTransitionTable();

    long long state_count = (long long)cornerOrientation.get_state_count() * (long long)cornerPermutation.get_state_count();

    if (!FileIO::read_char_vector(prune_table, file_path, state_count))
    {
        prune_table = vector<char>(state_count, 11);
        int visited_count = 0;
        char maxBreathDepthSearch = 8;

        for (char depth = 0; depth <= maxBreathDepthSearch; depth++) {
            pruneTreeSearch(0, 0, depth, depth, -1);
        }


        for (int i = 0; i < state_count; i++) {
            if (prune_table[i] < 11)
                continue;

            //Only the position smaller than 11, since 11 is max
            for (char depth = maxBreathDepthSearch + 1; depth < 11; depth++) {
                if (solveable(i % 2187, i / 2187, depth, maxBreathDepthSearch, -1)) {
                    prune_table[i] = depth;
                    break;
                }
            }
        }

        FileIO::store_char_vector(prune_table, file_path);
    }
}

void cornerPruning::pruneTreeSearch(long long orient_state, long long perm_state, char depth_left, char depth, int lastMove)
{
    long long state = perm_state * 2187 + orient_state;
    if (depth_left == 0)
    {
        if (prune_table[state] > depth)
        {
            prune_table[state] = depth;
        }
    }
    else
    {
        if (prune_table[state] == depth - depth_left)
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

bool cornerPruning::solveable(long long orient_state, long long perm_state, char depth, char maxBreathDepthSearch, int lastMove)
{
    long long state = perm_state * 2187 + orient_state;
    if (prune_table[state] == depth)
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
