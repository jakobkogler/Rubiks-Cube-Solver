#include "prune.h"
#include <iomanip>

void Prune::buildPruneTable(TransitionTable &transition_table, int state_count, int start_value)
{
    prune_table = Nibble32(state_count, 15);
    if (!prune_table.read(file_path)) {
        int visited_count = 0;
        char depth = 0;

        while (visited_count < state_count) {
            int cnt = pruneTreeSearch(start_value, prune_table, depth, depth, -1, transition_table);
            visited_count += cnt;
            depth++;
        }

        prune_table.store(file_path);
    }
}

void Prune::showPruneInfos(std::ostream& os) const {
    uint64_t sum = 0;
    std::vector<uint64_t> cnt(20, 0);
    for (uint64_t i = 0; i < prune_table.size(); i++) {
        int prune_value = prune_table.get({i >> 3, i & 7});
        sum += prune_value;
        cnt[prune_value]++;
    }
    os << file_path << std::endl;
    for (int i = 0; i < 20 && cnt[i]; i++) {
        os << "  " << std::setfill(' ') << std::setw(2) << i << ": " << cnt[i] << std::endl;
    }
    os << "Effective prune value: " << sum / (double)prune_table.size() << std::endl;
}

int Prune::pruneTreeSearch(int state, Nibble32 & table, int depth_left, int depth, int lastMove, TransitionTable &transition_table)
{
    int cnt = 0;

    if (depth_left == 0)
    {
        if (table.get(state) > depth)
        {
            table.set(state, depth);
            cnt = 1;
        }
    }
    else
    {
        if (table.get(state) == depth - depth_left)
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
