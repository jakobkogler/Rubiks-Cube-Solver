#pragma once

#include <vector>
#include <array>
#include "pruning_info.h"

using Table12 = std::array<int, 12>;

class Edges {
public:
    Edges() {}
    Edges(Table12 labels, int pieces_cnt);
    std::vector<int> edges_perm;
    std::vector<int> edges_orient;
    void apply_move(int move);
    std::pair<uint32_t, uint32_t> to_index() const;
    void from_index(uint64_t state);
    PruningInfo get_pruning_info() const;
private:
    int pieces_cnt;
    std::array<Table12, 6> perm, orient;
    std::vector<uint32_t> offsets;
    PruningInfo pruning_info;
};

constexpr uint64_t product(unsigned a, unsigned b)
{
    uint64_t res = 1u;
    for (auto x = a; x <= b; x++)
        res *= x;
    return res;
}

constexpr uint64_t factorial(unsigned x)
{
    return product(1, x);
}
