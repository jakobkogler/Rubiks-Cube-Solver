#include <iostream>
#include "optimal_solver.h"

using namespace std;

int main()
{
	OptimalSolver os;

	// two switched adjacent corners
	os.IDA(vector<int>{ 1, 0, 2, 3, 4, 5, 6, 7 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0 });

	// two switched opposite corners
	os.IDA(vector<int>{ 2, 1, 0, 3, 4, 5, 6, 7 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0 }, vector<int>{ 0, 0, 0, 0, 0, 0, 0, 0 });
}
