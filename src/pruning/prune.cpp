#include "prune.h"
#include "fileio.h"

void Prune::buildPruneTable(std::vector<std::vector<long long>> &transition_table, int state_count, int start_value)
{
    if (!FileIO::read_char_vector(prune_table, file_path, state_count))
    {
        prune_table = std::vector<char>(state_count, 20);

        int visited_count = 0;
        char depth = 0;

        while (visited_count < state_count) {
            int cnt = pruneTreeSearch(start_value, prune_table, depth, depth, -1, transition_table);
            visited_count += cnt;
            depth++;
        }

        FileIO::store_char_vector(prune_table, file_path);
    }
}

void Prune::showPruneInfos(std::ostream& os) const {
    long long sum = 0;
    for (int prune_value : prune_table) {
        sum += prune_value;
    }
    os << file_path << std::endl;
    os << "Effective prune value: " << sum / (double)prune_table.size() << std::endl;
}

int Prune::pruneTreeSearch(int state, std::vector<char> & table, char depth_left, char depth, int lastMove, std::vector<std::vector<long long>> &transition_table)
{
    int cnt = 0;

    if (depth_left == 0)
    {
        if (table[state] > depth)
        {
            table[state] = depth;
            cnt = 1;
        }
    }
    else
    {
        if (table[state] == depth - depth_left)
        {
            for (int move = 0; move < 6; move++)
            {
                if (move == lastMove)
                    continue;
                if ((lastMove & 1) == 1 && move == lastMove - 1)
                    continue;

                for (int j = 0; j < 3; j++)
                {
                    state = transition_table[state][move];
                    cnt += pruneTreeSearch(state, table, depth_left - 1, depth, move, transition_table);
                }
                state = transition_table[state][move];
            }
        }
    }

    return cnt;
}
