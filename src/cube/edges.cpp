#include "edges.h"
#include <numeric>

Table12 generatePermTable(int a, int b, int c, int d) {
    Table12 t;
    std::iota(t.begin(), t.end(), 0);
    t[a] = b;
    t[b] = c;
    t[c] = d;
    t[d] = a;
    return t;
}

std::array<int, 12> generateOrientTable(int a, int b, int c, int d) {
    Table12 t{ 0 };
    t[a] = t[b] = t[c] = t[d] = 1;
    return t;
}

Edges::Edges(int cnt) : cnt(cnt) {
    edges_perm.assign(cnt, 0);
    std::iota(edges_perm.begin(), edges_perm.end(), 0);
    edges_orient.assign(cnt, 0);

    perm[0] = generatePermTable(0, 1, 2, 3);
    perm[1] = generatePermTable(8, 11, 10, 9);
    perm[2] = generatePermTable(1, 5, 9, 6);
    perm[3] = generatePermTable(3, 7, 11, 4);
    perm[4] = generatePermTable(2, 6, 10, 7);
    perm[5] = generatePermTable(0, 4, 8, 5);
    orient[4] = generateOrientTable(2, 6, 10, 7);
    orient[5] = generateOrientTable(0, 4, 8, 5);
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
