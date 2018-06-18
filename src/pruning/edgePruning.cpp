#include "edgePruning.h"
#include <sstream>
#include <iostream>

const std::string create_file_path(std::initializer_list<int> const& il) {
    std::stringstream ss;
    ss << "edgePruning";
    for (int piece : il) {
        ss << piece;
    }
    ss << ".data";
    return ss.str();
}

edgePruning::edgePruning(int pieces_cnt)
    : pieces_cnt(pieces_cnt)
{
    file_path = "edgePruning0123456.data";
    buildPruneTable();
}

int edgePruning::pruning_number(Cube &cube)
{
    return prune_table[cube.edges.to_index()];
}

void edgePruning::buildPruneTable()
{
    long long state_count = product(12 - pieces_cnt + 1, 12) << pieces_cnt;
    std::cout << state_count << std::endl;

    prune_table = Nibble32(state_count, 15u);
    if (!prune_table.read(file_path)) {
        visited = 0;
        
        Cube cube;
        int maxBreathDepthSearch = pieces_cnt <= 6 ? 7 : 8;
        for (char depth = 0; depth <= maxBreathDepthSearch; depth++) {
            std::cout << (int)depth << std::endl;
            pruneTreeSearch(cube, depth, depth, -1);
        }

        int mask = (1 << 20) - 1;
        for (int state = 0; state < state_count; state++) {
            if ((state & mask) == mask)
                std::cout << state / (double)state_count * 100 << std::endl;
                
            if (prune_table[state] <= maxBreathDepthSearch)
                continue;

            cube.edges.to_array(state);

            for (char depth = maxBreathDepthSearch + 1; depth < 15; depth++) {
                if (solveable(cube, depth, maxBreathDepthSearch, -1)) {
                    prune_table.set(state, depth);
                    break;
                }
            }
        }

        prune_table.store(file_path);
    }
}

void edgePruning::pruneTreeSearch(Cube & cube, char depth_left, char depth, int lastMove)
{
    int state = cube.edges.to_index();
    if (depth_left == 0)
    {
        if (prune_table[state] > depth)
        {
            prune_table.set(state, depth);
            visited++;
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
                    cube.apply_move(move);
                    pruneTreeSearch(cube, depth_left - 1, depth, move);
                }
                cube.apply_move(move);
            }
        }
    }
}

bool edgePruning::solveable(Cube & cube, char depth, char maxBreathDepthSearch, int lastMove)
{
    int state = cube.edges.to_index();
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
                cube.apply_move(move);
                if (solveable(cube, depth - 1, maxBreathDepthSearch, move))
                {
                    return true;
                }
            }
            cube.apply_move(move);
        }

        return false;
    }
}
