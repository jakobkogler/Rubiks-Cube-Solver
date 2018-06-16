#ifndef EDGESECOND6PRUNING_H
#define EDGESECOND6PRUNING_H


#include "prune.h"

class edgeSecond6Pruning : public Prune {
public:
    edgeSecond6Pruning();
    int pruning_number(Cube &cube);
    int visited;
private:
    void buildPruneTable();
    void pruneTreeSearch(Cube & cube, char depth_left, char depth, int lastMove);
    int to_index(Cube const& cube) const;
    bool solveable(Cube & cube, char depth, char maxBreathDepthSearch, int lastMove);
};


#endif //EDGESECOND6PRUNING_H
