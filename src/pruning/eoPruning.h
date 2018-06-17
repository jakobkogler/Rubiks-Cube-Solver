#pragma once

#include "prune.h"

class eoPruning : public Prune {
public:
    eoPruning();
    int pruning_number(Cube &cube);
};
