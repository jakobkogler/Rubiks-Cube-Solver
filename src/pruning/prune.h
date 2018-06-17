#pragma once

#include "cube.h"
#include <vector>
#include <iostream>
#include "nibble.h"

class Prune {
protected:
    Nibble32 prune_table;
    std::string file_path;

public:
    virtual int pruning_number(Cube &cube) = 0;
    virtual void showPruneInfos(std::ostream& os) const;
    virtual ~Prune() {}
protected:
    void buildPruneTable(std::vector<std::vector<long long>> &transition_table, int state_count, int start_value = 0);
    int pruneTreeSearch(int state, Nibble32 & table, int depth_left, int depth, int lastMove, std::vector<std::vector<long long>> &transition_table);
};
