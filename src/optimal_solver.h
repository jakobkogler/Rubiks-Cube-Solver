#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class OptimalSolver
{
private:
	long prune_count;
	int nodeCnt;
	string solution;
	vector<vector<long> > co_transition, cp_transition, eo_transition, ep_transition;
	vector<int> c_prune, eo_prune, ep1_prune, ep2_prune;
	string moveNames[6], moveCntNames[3];
	unordered_map<long, int> e_prune;

public:
	OptimalSolver();
	int IDA(vector<int> cornerPermutation, vector<int> cornerOrientation, vector<int> edgeOrientation, vector<int> edgePermutation1, vector<int> edgePermutation2);
private: 
	bool treeSearch(int cornerPermutation, int cornerOrientation, int edgeOrientation, int edgePermutation1, int edgePermutation2, int depth, int lastMove);
	void prune_treeSearch(long ep1, long ep2, int depth_left, int depth, int lastMove);
};
