#include "edgePruning.h"
#include "fileio.h"
#include <sstream>
#include <iostream>

std::vector<int> computeOffsets(int cnt) {
    std::vector<int> arr(cnt);
    for (int i = 0; i < cnt; i++) {
        arr[i] = product(13 - cnt, 11 - i);
    }
    return arr;
}

const std::string create_file_path(std::initializer_list<int> const& il) {
    std::stringstream ss;
    ss << "edgePruning";
    for (int piece : il) {
        ss << piece;
    }
    ss << ".data";
    return ss.str();
}

edgePruning::edgePruning(std::initializer_list<int> const& il)
    : offsets(computeOffsets(il.size())), pieces_cnt(il.size()), pieces(il.begin(), il.end())
{
    file_path = create_file_path(il);
    buildPruneTable();
}

int edgePruning::to_index(Cube const& cube) const {
    unsigned long long cnt = 0xfedcba9876543210;
    int state = 0;
    auto const& perm = cube.edges.edges_perm;
    auto const& orient = cube.edges.edges_orient;
    for (int i = 0; i < pieces_cnt; i++) {
        int p4 = perm[pieces[i]] * 4;
        int x = (cnt >> p4) & 15;
        state += x * offsets[i];
        cnt -= 0x1111111111111110 << p4;
    }
    for (int i = 0; i < pieces_cnt; i++) {
        state = (state << 1) + orient[pieces[i]];
    }
    return state;
}

void edgePruning::to_array(int state, Cube & cube) {
    unsigned long long cnt = 0xfedcba9876543210;
    auto & perm = cube.edges.edges_perm;
    auto & orient = cube.edges.edges_orient;
    for (int i = 0; i < pieces_cnt; i++) {
        orient[pieces[i]] = (state >> (pieces_cnt - 1 - i)) & 1;
    }
    state >>= pieces_cnt;
    for (int i = 0; i < pieces_cnt; i++) {
        int p4 = (state / offsets[i]) * 4;
        perm[pieces[i]] = (cnt >> p4) & 15;
        unsigned long long mask = ((unsigned long long)1 << p4) - 1;
        cnt = (cnt & mask) | ((cnt >> 4) & ~mask);
        state %= offsets[i];
    }
}

int edgePruning::pruning_number(Cube &cube)
{
    return prune_table[to_index(cube)];
}

void edgePruning::buildPruneTable()
{
    long long state_count = product(12 - pieces_cnt + 1, 12) << pieces_cnt;

    prune_table = Nibble32(state_count, 15u);
    if (!prune_table.read(file_path)) {
        visited = 0;

        Cube cube;
        int maxBreathDepthSearch = pieces_cnt <= 6 ? 7 : 8;
        for (char depth = 0; depth <= maxBreathDepthSearch; depth++) {
            std::cout << (int)depth << std::endl;
            pruneTreeSearch(cube, depth, depth, -1);
        }

        for (int state = 0; state < state_count; state++) {
            if (prune_table[state] <= maxBreathDepthSearch)
                continue;

            to_array(state, cube);

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
    int state = to_index(cube);
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
    int state = to_index(cube);
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
