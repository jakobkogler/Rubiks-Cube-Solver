#include <vector>

using namespace std;

class Indexing
{
public:
	static int permutation_to_index(vector<int> const& arr);
	static void index_to_permutation(int index, vector<int> & arr);
	static int orientation_to_index_dependent(vector<int> const& arr, int orientation_cnt);
	static void index_to_orientation_dependent(int index, vector<int> & arr, int orientation_cnt);
	static int orientation_to_index(vector<int> const& arr, int orientation_cnt);
	static void index_to_orientation(int index, vector<int> & arr, int orientation_cnt);
};
