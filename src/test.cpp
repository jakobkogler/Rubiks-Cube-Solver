#include <iostream>
#include "optimal_solver.h"

using namespace std;

int main()
{
	OptimalSolver os;

	// A-perm
	os.IDA(vector<int>{ 1, 2, 0, 3, 4, 5, 6, 7 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0 }, vector<int>{ 0, 1, 2, 3, 4, 5 }, vector<int>{ 6, 7, 8, 9, 10, 11, 12 });

	// E-perm
	os.IDA(vector<int>{ 1, 0, 3, 2, 4, 5, 6, 7 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0 }, vector<int>{ 0, 1, 2, 3, 4, 5 }, vector<int>{ 6, 7, 8, 9, 10, 11, 12 });
}
