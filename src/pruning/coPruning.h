#ifndef COPRUNING_H
#define COPRUNING_H

#include "prune.h"

class coPruning : public Prune {
public:
    coPruning();
    int pruning_number(Cube &cube);
};

#endif //COPRUNING_H
