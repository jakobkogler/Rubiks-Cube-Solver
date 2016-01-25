#ifndef CPPRUNING_H
#define CPPRUNING_H

#include "prune.h"

class cpPruning : public Prune {
public:
    cpPruning();
    int pruning_number(Cube &cube);
};

#endif //CPPRUNING_H
