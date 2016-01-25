#ifndef EDGEPRUNING_H
#define EDGEPRUNING_H

#include <unordered_map>
#include "prune.h"

class edgePruning : public Prune{
private:
    unordered_map<long long, char> pruning_map;
    long long prune_count;

public:
    edgePruning();
    int pruning_number(Cube &cube);
private:
    void buildPruneTable(vector<vector<long long>> &transition_table, int state_count, int start_value = 0);
    void prune_treeSearch(vector<vector<long long>> &transition_table, long long ep1, long long ep2, char depth_left, char depth, int lastMove);
};

#endif //EDGEPRUNING_H
