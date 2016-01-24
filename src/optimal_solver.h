#include <vector>
#include <string>
#include <unordered_map>
#include "cube.h"

using namespace std;

class OptimalSolver
{
private:
    long long nodeCnt;
    string solution;
    string moveNames[6], moveCntNames[3];

public:
    OptimalSolver();
    char solve(string scramble);
    char IDA(Cube &cube);
    
private: 
    bool treeSearch(Cube &cube, char depth, int lastMove);
};
