#include <iostream>
#include "optimal_solver.h"

using namespace std;

int main()
{
	OptimalSolver os;

	// A-perm
	os.IDA(vector<int>{ 2, 0, 1, 3, 4, 5, 6, 7 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, vector<int>{ 0, 1, 2, 3, 4, 5 }, vector<int>{ 6, 7, 8, 9, 10, 11, 12 });

	// E-perm
	os.IDA(vector<int>{ 1, 0, 3, 2, 4, 5, 6, 7 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, vector<int>{ 0, 1, 2, 3, 4, 5 }, vector<int>{ 6, 7, 8, 9, 10, 11, 12 });

	// T-perm
	os.IDA(vector<int>{ 0, 2, 1, 3, 4, 5, 6, 7 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, vector<int>{ 0, 3, 2, 1, 4, 5 }, vector<int>{ 6, 7, 8, 9, 10, 11, 12 });

	// Y-perm
	os.IDA(vector<int>{ 2, 1, 0, 3, 4, 5, 6, 7 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, vector<int>{ 3, 1, 2, 0, 4, 5 }, vector<int>{ 6, 7, 8, 9, 10, 11, 12 });

	// Z-perm
	os.IDA(vector<int>{ 0, 1, 2, 3, 4, 5, 6, 7 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, vector<int>{ 1, 0, 3, 2, 4, 5 }, vector<int>{ 6, 7, 8, 9, 10, 11, 12 });

	//random
	os.IDA(vector<int>{ 2, 4, 6, 0, 3, 1, 7, 5 }, vector<int>{ 0, 0, 0, 0, 0, 1, 1, 1 }, vector<int>{ 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1 }, vector<int>{ 4, 9, 1, 2, 8, 7 }, vector<int>{ 3, 11, 10, 5, 6, 0 });
}
