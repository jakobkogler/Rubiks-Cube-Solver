#include <vector>

class Edges {
public:
    Edges();
    std::vector<int> edges_perm;
    std::vector<int> edges_orient;
    void apply_move(int move);
};
