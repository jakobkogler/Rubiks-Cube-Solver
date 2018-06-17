#include <vector>

class Indexing
{
public:
    static int permutation_to_index(std::vector<int> const& arr);
    static void index_to_permutation(int index, std::vector<int> & arr);
    static int orientation_to_index_dependent(std::vector<int> const& arr, int orientation_cnt);
    static void index_to_orientation_dependent(int index, std::vector<int> & arr, int orientation_cnt);
    static int orientation_to_index(std::vector<int> const& arr, int orientation_cnt);
    static void index_to_orientation(int index, std::vector<int> & arr, int orientation_cnt);
};
