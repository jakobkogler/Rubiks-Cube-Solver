#ifndef PRUNE_H
#define PRUNE_H

#include "cube.h"
#include <vector>
#include <iostream>

class Prune {
protected:
    std::vector<char> prune_table;
    std::string file_path;

public:
    virtual int pruning_number(Cube &cube) = 0;
    virtual void showPruneInfos(std::ostream& os) const;
protected:
    void buildPruneTable(std::vector<std::vector<long long>> &transition_table, int state_count, int start_value = 0);
    int pruneTreeSearch(int state, std::vector<char> & table, char depth_left, char depth, int lastMove, std::vector<std::vector<long long>> &transition_table);
};


#endif //PRUNE_H
