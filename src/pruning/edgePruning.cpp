#include "edgePruning.h"
#include <sstream>
#include <iostream>

const std::string create_file_path(int pieces_cnt) {
    std::stringstream ss;
    ss << "edgePruning";
    for (int i = 0; i < pieces_cnt; i++) {
        ss << i;
    }
    ss << ".data";
    return ss.str();
}

edgePruning::edgePruning(int pieces_cnt)
    : pieces_cnt(pieces_cnt)
{
    file_path = create_file_path(pieces_cnt);
    buildPruneTable();
}

int edgePruning::pruning_number(Edges &edges)
{
    return prune_table.get(edges.to_index());
}

void edgePruning::buildPruneTable()
{
    long long state_count = product(12 - pieces_cnt + 1, 12) << pieces_cnt;
    std::cout << state_count << std::endl;

    prune_table = Nibble32(state_count, 15u);
    if (!prune_table.read(file_path)) {
        visited = 0;
        
        Edges edges({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, pieces_cnt);
        int maxBreathDepthSearch = pieces_cnt <= 6 ? 7 : 8;
        for (char depth = 0; depth <= maxBreathDepthSearch; depth++) {
            std::cout << (int)depth << std::endl;
            pruneTreeSearch(edges, depth, depth, -1);
        }

        int mask = (1 << 20) - 1;
        for (int state = 0; state < state_count; state++) {
            if ((state & mask) == mask)
                std::cout << state / (double)state_count * 100 << std::endl;
                
            if (prune_table.get(state) <= maxBreathDepthSearch)
                continue;

            edges.to_array(state);

            for (char depth = maxBreathDepthSearch + 1; depth < 15; depth++) {
                if (solveable(edges, depth, maxBreathDepthSearch, -1)) {
                    prune_table.set(state, depth);
                    break;
                }
            }
        }

        prune_table.store(file_path);
    }
}

void edgePruning::pruneTreeSearch(Edges & edges, char depth_left, char depth, int lastMove)
{
    auto state = edges.to_index();
    if (depth_left == 0)
    {
        if (prune_table.get(state) > depth)
        {
            prune_table.set(state, depth);
            visited++;
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
                    edges.apply_move(move);
                    pruneTreeSearch(edges, depth_left - 1, depth, move);
                }
                edges.apply_move(move);
            }
        }
    }
}

bool edgePruning::solveable(Edges & edges, char depth, char maxBreathDepthSearch, int lastMove)
{
    auto state = edges.to_index();
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
                edges.apply_move(move);
                if (solveable(edges, depth - 1, maxBreathDepthSearch, move))
                {
                    return true;
                }
            }
            edges.apply_move(move);
        }

        return false;
    }
}
