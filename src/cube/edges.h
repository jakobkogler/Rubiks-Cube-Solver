#include <vector>
#include <array>

using Table12 = std::array<int, 12>;

class Edges {
public:
    Edges() {}
    Edges(Table12 labels, int pieces_cnt);
    std::vector<int> edges_perm;
    std::vector<int> edges_orient;
    void apply_move(int move);
    std::pair<uint32_t, uint32_t> to_index() const;
    void to_array(uint32_t state);
private:
    int pieces_cnt;
    std::array<Table12, 6> perm, orient;
    std::vector<int> offsets;
};

constexpr int product(int a, int b)
{
    int res = 1;
    for (int x = a; x <= b; x++)
        res *= x;
    return res;
}

constexpr int factorial(int x)
{
    return product(1, x);
}
