#pragma once

#include "prune.h"

class coPruning : public Prune {
public:
    coPruning();
    int pruning_number(Cube &cube);
};
