#pragma once

#include "prune.h"

class ep2Pruning : public Prune {
public:
    ep2Pruning();
    int pruning_number(Cube &cube);
};
