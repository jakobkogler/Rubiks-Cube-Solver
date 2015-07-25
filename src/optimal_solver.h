#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class OptimalSolver
{
private:
	long prune_count;
	long nodeCnt;
	string solution;
	vector<vector<long> > co_transition, cp_transition, eo_transition, ep_transition;
	vector<char> c_prune, eo_prune, ep1_prune, ep2_prune;
	string moveNames[6], moveCntNames[3];
	unordered_map<long, char> e_prune;

public:
	OptimalSolver();
	char solve(string scramble);
	char IDA(vector<int> cornerPermutation, vector<int> cornerOrientation, vector<int> edgeOrientation, vector<int> edgePermutation1, vector<int> edgePermutation2);
	
private: 
	bool treeSearch(int cornerPermutation, int cornerOrientation, int edgeOrientation, int edgePermutation1, int edgePermutation2, char depth, int lastMove);
	void prune_treeSearch(long ep1, long ep2, char depth_left, char depth, int lastMove);
	void apply_scramble(string scramble, vector<int> &cp_vec, vector<int> &co_vec, vector<int> &eo_vec, vector<int> &ep1_vec, vector<int> &ep2_vec);
};
