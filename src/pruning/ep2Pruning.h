#ifndef EP2PRUNING_H
#define EP2PRUNING_H

#include "prune.h"

class ep2Pruning : public Prune {
public:
    ep2Pruning();
    int pruning_number(Cube &cube);
};

#endif //EP2PRUNING_H
