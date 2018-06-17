#pragma once

#include "prune.h"

class ep1Pruning : public Prune {
public:
    ep1Pruning();
    int pruning_number(Cube &cube);
};
