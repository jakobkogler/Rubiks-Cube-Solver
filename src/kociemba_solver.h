#include <vector>
#include <string>
#include <unordered_map>
#include "cube.h"
#include "Phase1Pruning.h"

using namespace std;

class KociembaSolver
{
private:
    long long nodeCnt;
    string solution;
    string moveNames[6] = {"U", "D", "R", "L", "F", "B"};
    string moveCntNames[3] = {" ", "2", "'"};
    Phase1Pruning phase1pruning;

public:
    KociembaSolver();
    ~KociembaSolver();
    char solve(string scramble);
    char IDA(Cube &cube);
    
private: 
    bool treeSearch(Cube &cube, char depth, int lastMove);
};
