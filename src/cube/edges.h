#include <vector>

using namespace std;

class Edges {
public:
    Edges();
    vector<int> edges_perm;
    vector<int> edges_orient;
    void apply_move(int move);
};
