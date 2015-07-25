#ifndef CORNER_H
#define CORNER_H

#include <vector>
#include <string>

using namespace std;

class Corner
{
private:
	vector<vector<long> > permutation_transition_table, orientation_transition_table;
	vector<char> prune_table;
	int state_count;
	string prune_file_path;

public:
	Corner(vector<vector<long> > & permutation_transition_table, vector<vector<long> > & orientation_transition_table)
		: permutation_transition_table(permutation_transition_table), orientation_transition_table(orientation_transition_table), 
		  state_count(88179840, prune_file_path("corner_prune.data")) {}
	void buildPruneTable();
	vector<char> getPruneTable(){ return prune_table; }
private:
	void pruneTreeSearch(long state, char depth_left, char depth, int lastMove);
	long apply_transition(long state, int move);
	bool solveable(long state, char depth, char maxBreathDepthSearch, int lastMove);
	void store_to_file_prune(string path);
	bool try_read_from_file(string path);
};

#endif // CORNER_H
