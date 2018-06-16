#include "edgeFirst6Pruning.h"
#include "fileio.h"
#include <iostream>

edgeFirst6Pruning::edgeFirst6Pruning()
{
    file_path = "edgeFirst6Pruning.data";

    buildPruneTable();
}

int edgeFirst6Pruning::to_index(Cube const& cube) const {
    unsigned long long mask = 0xfedcba9876543210;
    int state = 0;
    auto const& perm = cube.edges.edges_perm;
    auto const& orient = cube.edges.edges_orient;
    static const array<int, 6> f = { 11 * 10 * 9 * 8 * 7, 10 * 9 * 8 * 7, 9 * 8 * 7, 8 * 7, 7, 1 };
    for (int i = 0; i < 6; i++) {
        int p4 = perm[i] * 4;
        int x = (mask >> p4) & 15;
        state += x * f[i];
        mask -= 0x1111111111111110 << p4;
    }
    for (int i = 0; i < 6; i++) {
        state = (state << 1) + orient[i];
    }
    return state;
}

int edgeFirst6Pruning::pruning_number(Cube &cube)
{
    return prune_table[to_index(cube)];
}

void edgeFirst6Pruning::buildPruneTable()
{
    long long state_count = (12 * 11 * 10 * 9 * 8 * 7) << 6;

    if (!FileIO::read_char_vector(prune_table, file_path, state_count))
    {
        prune_table = vector<char>(state_count, 20);
        visited = 0;

        Cube cube;
        int maxBreathDepthSearch = 7;
        for (char depth = 0; depth <= maxBreathDepthSearch; depth++) {
            pruneTreeSearch(cube, depth, depth, -1);
        }

        for (int a = 0; a < 12; a++) {
            for (int b = 0; b < 12; b++) {
                if (b == a) continue;
                for (int c = 0; c < 12; c++) {
                    if (c == a || c == b) continue;
                    for (int d = 0; d < 12; d++) {
                        if (d == a || d == b || d == c) continue;
                        for (int e = 0; e < 12; e++) {
                            if (e == a || e == b || e == c || e == d) continue;
                            for (int f = 0; f < 12; f++) {
                                if (f == a || f == b || f == c || f == d || f == e) continue;
                                auto& perm = cube.edges.edges_perm;
                                auto& orient = cube.edges.edges_orient;
                                for (int i = 0; i < (1 << 6); i++) {
                                    perm[0] = a;
                                    perm[1] = b;
                                    perm[2] = c;
                                    perm[3] = d;
                                    perm[4] = e;
                                    perm[5] = f;
                                    for (int j = 0; j < 6; j++)
                                        orient[j] = (i >> j) & 1;

                                    int state = to_index(cube);
                                    if (prune_table[state] <= maxBreathDepthSearch)
                                        continue;

                                    for (char depth = maxBreathDepthSearch + 1; depth < 15; depth++) {
                                        if (solveable(cube, depth, maxBreathDepthSearch, -1)) {
                                            prune_table[state] = depth;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        FileIO::store_char_vector(prune_table, file_path);
    }
}

void edgeFirst6Pruning::pruneTreeSearch(Cube & cube, char depth_left, char depth, int lastMove)
{
    int state = to_index(cube);
    if (depth_left == 0)
    {
        if (prune_table[state] > depth)
        {
            prune_table[state] = depth;
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

bool edgeFirst6Pruning::solveable(Cube & cube, char depth, char maxBreathDepthSearch, int lastMove)
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
