#include <vector>
#include <array>

using Table12 = std::array<int, 12>;

class Edges {
public:
    Edges() {}
    Edges(Table12 labels, int cnt);
    std::vector<int> edges_perm;
    std::vector<int> edges_orient;
    void apply_move(int move);
private:
    int cnt;
    std::array<Table12, 6> perm, orient;
};
