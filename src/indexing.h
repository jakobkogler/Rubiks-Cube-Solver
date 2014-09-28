class Indexing
{
public:
	static int permutation_to_index(int *arr, int n);
	static void index_to_permutation(int index, int *arr, int n);
	static int orientation_to_index_dependent(int *arr, int n, int orientation_cnt);
	static void index_to_orientation_dependent(int index, int *arr, int n, int orientation_cnt);
};
