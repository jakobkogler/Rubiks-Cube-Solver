#pragma once

#include "prune.h"

class cpPruning : public Prune {
public:
    cpPruning();
    int pruning_number(Cube &cube);
};
