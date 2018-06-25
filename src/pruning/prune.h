#pragma once

#include <iostream>
#include <iomanip>
#include "nibble.h"
#include "pruning_info.h"

template <typename Group>
class Prune
{
public:
    int pruning_number(Group const& group);
    void buildPruneTable(Group & group);
    void pruneTreeSearch(Group & group, int depth_left, int depth, int lastMove);
    bool solveable(Group & group, int depth, int maxBreathDepthSearch, int lastMove);
    void showPruneInfos(std::ostream& os) const;

private:
    Nibble32 prune_table;
    PruningInfo info;
    uint64_t visited;
};

template <typename Group>
int Prune<Group>::pruning_number(Group const& group)
{
    return prune_table.get(group.to_index());
}

template <typename Group>
void Prune<Group>::buildPruneTable(Group & group)
{
    info = group.get_pruning_info();
    std::cout << info.state_count << std::endl;

    prune_table = Nibble32(info.state_count, info.maxDepth);
    if (!prune_table.read(info.pruning_file)) {
        visited = 0;
        
        group.from_index(0);
        for (char depth = 0; depth <= info.maxDepthBFS; depth++) {
            std::cout << (int)depth << std::endl;
            pruneTreeSearch(group, depth, depth, -1);
        }

        uint64_t mask = (1 << 23) - 1;
        for (uint64_t state = 0; state < info.state_count; state++) {
            if ((state & mask) == mask)
                std::cout << state / static_cast<double>(info.state_count) * 100 << "%" << std::endl;
                
            std::pair<uint32_t, uint32_t> idx = {state >> 3, state & 7};
            if (prune_table.get(idx) <= info.maxDepthBFS)
                continue;

            group.from_index(state);
            for (int depth = info.maxDepthBFS + 1; depth < info.maxDepth; depth++) {
                if (solveable(group, depth, info.maxDepthBFS, -1)) {
                    prune_table.set(idx, depth);
                    break;
                }
            }
        }

        prune_table.store(info.pruning_file);
    }
}

template <typename Group>
void Prune<Group>::pruneTreeSearch(Group & group, int depth_left, int depth, int lastMove)
{
    auto index = group.to_index();
    if (depth_left == 0) {
        if (prune_table.get(index) > depth) {
            prune_table.set(index, depth);
            visited++;
        }
    } else {
        if (prune_table.get(index) == depth - depth_left) {
            for (int move = 0; move < 6; move++) {
                if (move == lastMove)
                    continue;
                if ((lastMove & 1) == 1 && move == lastMove - 1)
                    continue;

                for (int j = 0; j < 3; j++) {
                    group.apply_move(move);
                    pruneTreeSearch(group, depth_left - 1, depth, move);
                }
                group.apply_move(move);
            }
        }
    }
}

template <typename Group>
bool Prune<Group>::solveable(Group & group, int depth, int maxBreathDepthSearch, int lastMove)
{
    auto index = group.to_index();
    if (prune_table.get(index) == depth) {
        return true;
    } else if (depth <= maxBreathDepthSearch) {
        return false;
    } else {
        for (int move = 0; move < 6; move++) {
            if (move == lastMove)
                continue;
            if ((lastMove & 1) == 1 && move == lastMove - 1)
                continue;

            for (int j = 0; j < 3; j++) {
                group.apply_move(move);
                if (solveable(group, depth - 1, maxBreathDepthSearch, move))
                    return true;
            }
            group.apply_move(move);
        }
        return false;
    }
}

template <typename Group>
void Prune<Group>::showPruneInfos(std::ostream& os) const
{
    uint64_t sum = 0;
    std::vector<uint64_t> cnt(20, 0);
    for (uint64_t state = 0; state < info.state_count; state++) {
        int prune_value = prune_table.get({state >> 3, state & 7});
        sum += prune_value;
        cnt[prune_value]++;
    }
    os << info.pruning_file << std::endl;
    for (int i = 0; i < 20 && cnt[i]; i++) {
        os << "  " << std::setfill(' ') << std::setw(2) << i << ": " << cnt[i] << std::endl;
    }
    os << "Effective prune value: " << sum / static_cast<double>(prune_table.size()) << std::endl;
}
