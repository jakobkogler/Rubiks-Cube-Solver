#ifndef EPPRUNING_H
#define EPPRUNING_H

#include "prune.h"

class epPruning : public Prune {
public:
    epPruning();
    int pruning_number(Cube &cube);
};

#endif //EPPRUNING_H
