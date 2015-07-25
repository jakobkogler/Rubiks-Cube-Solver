#ifndef CORNER_H
#define CORNER_H

#include <vector>
#include <string>

using namespace std;

class Corner
{
private:
	vector<vector<long> > permutation_transition_table, orientation_transition_table;
	vector<int> prune_table;
	int state_count;

public:
	Corner(vector<vector<long> > & permutation_transition_table, vector<vector<long> > & orientation_transition_table)
		: permutation_transition_table(permutation_transition_table), 
		orientation_transition_table(orientation_transition_table), state_count(88179840) {}
	void buildPruneTable();
	vector<int> getPruneTable(){ return prune_table; }
private:
	void pruneTreeSearch(long state, int depth_left, int depth, int lastMove);
	long apply_transition(long state, int move);
	bool solveable(int state, int depth, int maxBreathDepthSearch, int lastMove);
	void store_to_file_prune(string path);
	bool try_read_from_file(string path);
};

#endif // CORNER_H
