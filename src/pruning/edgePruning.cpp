#include "edgePruning.h"
#include "fileio.h"

edgePruning::edgePruning()
{
    file_path = "edgePruning.data";

    EdgePermutation edgePermutation;
    edgePermutation.buildTransitionTable();
    vector<vector<long long>> transition_table = edgePermutation.getTransitionTable();

    buildPruneTable(transition_table, edgePermutation.get_state_count());
}

int edgePruning::pruning_number(Cube &cube)
{
    long long p = cube.getEpState1() * 665280L + cube.getEpState2();
    char ep_prune_value = edges_combined_max;
    auto it = pruning_map.find(p);
    if (it != pruning_map.end())
        ep_prune_value = it->second;
    return ep_prune_value;
}

void edgePruning::showPruneInfos(ostream& os) const
{
    long long sum = 0;
    for (pair<long long, int> const& p : pruning_map) {
        sum += p.second;
    }
    long long total = 479001600;
    sum += (total - pruning_map.size()) * edges_combined_max;
    os << file_path << endl;
    os << "Effective prune value: " << sum / (double)total << endl;
}

void edgePruning::buildPruneTable(vector<vector<long long>> &transition_table, int state_count, int start_value)
{
    prune_count = 0;
    pruning_map.clear();
    char depth = 0;
    edges_combined_max = 8;
    long long max = 12 * 11 * 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1;

    if (!FileIO::read_unordered_map(pruning_map, file_path, 73596790))
    {
        while (prune_count < max && depth < edges_combined_max)
        {
            prune_treeSearch(transition_table, 0, 366288, depth, depth, -1);
            depth++;
        }

        FileIO::store_unordered_map(pruning_map, file_path);
    }
}

void edgePruning::prune_treeSearch(vector<vector<long long>> &transition_table, long long ep1, long long ep2, char depth_left, char depth, int lastMove)
{
    long long p = ep1 * 665280 + ep2;

    if (depth_left == 0)
    {
        if (pruning_map.count(p) == 0)
        {
            pruning_map[p] = depth;
            prune_count++;
        }
    }
    else
    {
        if (pruning_map[p] == depth - depth_left)
        {
            for (int move = 0; move < 6; move++)
            {
                if (move == lastMove)
                    continue;
                if ((lastMove & 1) == 1 && move == lastMove - 1)
                    continue;

                for (int j = 0; j < 3; j++)
                {
                    ep1 = transition_table[ep1][move];
                    ep2 = transition_table[ep2][move];
                    prune_treeSearch(transition_table, ep1, ep2, depth_left - 1, depth, move);
                }
                ep1 = transition_table[ep1][move];
                ep2 = transition_table[ep2][move];
            }
        }
    }
}
