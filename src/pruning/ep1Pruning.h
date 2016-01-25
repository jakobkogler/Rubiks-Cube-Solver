#ifndef EP1PRUNING_H
#define EP1PRUNING_H

#include "prune.h"

class ep1Pruning : public Prune {
public:
    ep1Pruning();
    int pruning_number(Cube &cube);
};

#endif //EP1PRUNING_H
