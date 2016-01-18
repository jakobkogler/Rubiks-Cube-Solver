#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <string>

using namespace std;

class Group
{
protected: 
    int state_count;
    int piece_count;
    vector<vector<long long> > transition_table;
    vector<char> prune_table;
    string prune_file_path;
    
public:
    vector<vector<long long> > getTransitionTable(){ return transition_table; }
    vector<char> getPruneTable(){ return prune_table; }
    void buildTransitionTable();
    void buildPruneTable();
    virtual void apply_move(vector<int> & arr, int move) = 0;
protected:
    Group(int state_count, int piece_count, string prune_file_path)
     : state_count(state_count), piece_count(piece_count), prune_file_path(prune_file_path) {}
    virtual void index_to_array(int index, vector<int> & arr) = 0;
    virtual int array_to_index(vector<int> const& arr) = 0;
    int pruneTreeSearch(int state, vector<char> & table, char depth_left, char depth, int lastMove);
};

#endif // GROUP_H
