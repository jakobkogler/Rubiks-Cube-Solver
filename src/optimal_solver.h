#include <vector>
#include <string>

using namespace std;

class OptimalSolver
{
private:
	int nodeCnt;
	string solution;
	vector<vector<long> > co_transition, cp_transition, eo_transition, ep_transition;
	vector<int> c_prune, eo_prune, ep1_prune, ep2_prune;
	string moveNames[6], moveCntNames[3];

public:
	OptimalSolver();
	int IDA(vector<int> cornerPermutation, vector<int> cornerOrientation, vector<int> edgeOrientation, vector<int> edgePermutation1, vector<int> edgePermutation2);
private: 
	bool OptimalSolver::treeSearch(int cornerPermutation, int cornerOrientation, int edgeOrientation, int edgePermutation1, int edgePermutation2, int depth, int lastMove);
};
