#ifndef PHASE1PRUNING_H
#define PHASE1PRUNING_H

#include "prune.h"


class Phase1Pruning : public Prune {
private:
    vector<vector<long long>> coTransition, eoTransition, UDSliceTransition;
public:
    Phase1Pruning();
    int pruning_number(Cube &cube);
private:
    void buildPruneTable();
};


#endif //PHASE1PRUNING_H
