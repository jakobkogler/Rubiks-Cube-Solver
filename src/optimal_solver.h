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
	char IDA(vector<int> cornerPermutation, vector<int> cornerOrientation, vector<int> edgeOrientation, vector<int> edgePermutation1, vector<int> edgePermutation2);
private: 
	bool treeSearch(int cornerPermutation, int cornerOrientation, int edgeOrientation, int edgePermutation1, int edgePermutation2, char depth, int lastMove);
	void prune_treeSearch(long ep1, long ep2, char depth_left, char depth, int lastMove);
};
