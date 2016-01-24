#ifndef EOPRUNING_H
#define EOPRUNING_H

#include "prune.h"

class eoPruning : public Prune {
public:
    eoPruning();
    int pruning_number(Cube &cube);
};

#endif //EOPRUNING_H
