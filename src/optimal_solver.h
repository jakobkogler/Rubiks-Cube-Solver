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
    string moveNames[6] = {"U", "D", "R", "L", "F", "B"};
    string moveCntNames[3] = {" ", "2", "'"};

public:
    OptimalSolver() {};
    char solve(string scramble);
    char IDA(Cube &cube);
    
private: 
    bool treeSearch(Cube &cube, char depth, int lastMove);
};
