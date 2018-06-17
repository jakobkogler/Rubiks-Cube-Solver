#ifndef EDGEFIRST6PRUNING_H
#define EDGEFIRST6PRUNING_H


#include "prune.h"
#include <array>

class edgeFirst6Pruning : public Prune {
public:
    edgeFirst6Pruning();
    int pruning_number(Cube &cube);
    int visited;
private:
    void buildPruneTable();
    void pruneTreeSearch(Cube & cube, char depth_left, char depth, int lastMove);
    int to_index(Cube const& cube) const;
    void to_array(int state, Cube & cube);
    bool solveable(Cube & cube, char depth, char maxBreathDepthSearch, int lastMove);

    const array<int, 6> offsets;
};


constexpr int product(int a, int b) {
    int res = 1;
    for (int x = a; x <= b; x++)
        res *= x;
    return res;
}

constexpr int factorial(int x) {
    return product(1, x);
}


#endif //EDGEFIRST6PRUNING_H
