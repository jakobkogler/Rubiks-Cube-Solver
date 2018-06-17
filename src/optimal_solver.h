#include <vector>
#include <string>
#include <unordered_map>
#include "cube.h"
#include "prune.h"

class OptimalSolver
{
private:
    long long nodeCnt;
    std::string solution;
    std::string moveNames[6] = {"U", "D", "R", "L", "F", "B"};
    std::string moveCntNames[3] = {" ", "2", "'"};
    std::vector<Prune*> pruning;

public:
    OptimalSolver();
    ~OptimalSolver();
    char solve(std::string scramble);
    char IDA(Cube &cube);
    
private: 
    bool treeSearch(Cube &cube, char depth, int lastMove);
};
