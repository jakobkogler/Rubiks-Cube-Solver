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

Edges::Edges(Table12 labels, int cnt) : cnt(cnt) {
    edges_perm.assign(cnt, 0);
    std::iota(edges_perm.begin(), edges_perm.end(), 0);
    edges_orient.assign(cnt, 0);

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
        for (int i = 0; i < cnt; i++) {
            edges_perm[i] = p[edges_perm[i]];
        }
    } else {
        for (int i = 0; i < cnt; i++) {
            edges_orient[i] ^= o[edges_perm[i]];
            edges_perm[i] = p[edges_perm[i]];
        }
    }
}
