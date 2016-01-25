#ifndef GROUP_H
#define GROUP_H

#include <vector>

using namespace std;

class Group
{
protected:
    int state_count;
    int piece_count;
    vector<vector<long long>> transition_table;

public:
    vector<vector<long long>> getTransitionTable(){ return transition_table; }
    void buildTransitionTable();
    virtual void apply_move(vector<int> & arr, int move) = 0;
    int get_state_count(){ return state_count; }
protected:
    Group(int state_count, int piece_count) : state_count(state_count), piece_count(piece_count) {}
    virtual void index_to_array(int index, vector<int> & arr) = 0;
    virtual int array_to_index(vector<int> const& arr) = 0;
};

#endif //GROUP_H
