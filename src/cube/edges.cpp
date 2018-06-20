#include "edges.h"
#include <numeric>

Table12 generatePermTable(Table12 const& labels, int a, int b, int c, int d) {
    Table12 t;
    std::iota(t.begin(), t.end(), 0);
    t[labels[a]] = labels[b];
    t[labels[b]] = labels[c];
    t[labels[c]] = labels[d];
    t[labels[d]] = labels[a];
    return t;
}

std::array<int, 12> generateOrientTable(Table12 const& labels, int a, int b, int c, int d) {
    Table12 t{ 0 };
    t[labels[a]] = t[labels[b]] = t[labels[c]] = t[labels[d]] = 1;
    return t;
}

std::vector<int> computeOffsets(int cnt)
{
    std::vector<int> arr(cnt);
    for (int i = 0; i < cnt; i++) {
        arr[i] = product(13 - cnt, 11 - i);
    }
    return arr;
}

Edges::Edges(Table12 labels, int pieces_cnt)
    : pieces_cnt(pieces_cnt), offsets(computeOffsets(pieces_cnt))
{
    edges_perm.assign(pieces_cnt, 0);
    std::iota(edges_perm.begin(), edges_perm.end(), 0);
    edges_orient.assign(pieces_cnt, 0);

    perm[0] = generatePermTable(labels, 0, 1, 2, 3);
    perm[1] = generatePermTable(labels, 8, 11, 10, 9);
    perm[2] = generatePermTable(labels, 1, 5, 9, 6);
    perm[3] = generatePermTable(labels, 3, 7, 11, 4);
    perm[4] = generatePermTable(labels, 2, 6, 10, 7);
    perm[5] = generatePermTable(labels, 0, 4, 8, 5);
    orient[4] = generateOrientTable(labels, 2, 6, 10, 7);
    orient[5] = generateOrientTable(labels, 0, 4, 8, 5);
}

void Edges::apply_move(int move) {
    auto const& p = perm[move];
    auto const& o = orient[move];
    if (move < 4) {
        for (int i = 0; i < pieces_cnt; i++) {
            edges_perm[i] = p[edges_perm[i]];
        }
    } else {
        for (int i = 0; i < pieces_cnt; i++) {
            edges_orient[i] ^= o[edges_perm[i]];
            edges_perm[i] = p[edges_perm[i]];
        }
    }
}

uint_fast32_t Edges::to_index() const {
    unsigned long long cnt = 0xfedcba9876543210;
    uint_fast32_t state = 0;
    for (int i = 0; i < pieces_cnt; i++) {
        int p4 = edges_perm[i] * 4;
        int x = (cnt >> p4) & 15;
        state += x * offsets[i];
        cnt -= 0x1111111111111110 << p4;
    }
    for (int i = 0; i < pieces_cnt; i++) {
        state = (state << 1) + edges_orient[i];
    }
    return state;
}

void Edges::to_array(uint_fast32_t state) {
    unsigned long long cnt = 0xfedcba9876543210;
    for (int i = 0; i < pieces_cnt; i++) {
        edges_orient[i] = (state >> (pieces_cnt - 1 - i)) & 1;
    }
    state >>= pieces_cnt;
    for (int i = 0; i < pieces_cnt; i++) {
        int p4 = (state / offsets[i]) * 4;
        edges_perm[i] = (cnt >> p4) & 15;
        unsigned long long mask = ((unsigned long long)1 << p4) - 1;
        cnt = (cnt & mask) | ((cnt >> 4) & ~mask);
        state %= offsets[i];
    }
}
