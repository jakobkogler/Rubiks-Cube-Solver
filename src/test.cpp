#include <iostream>
#include "optimal_solver.h"

using namespace std;

int main()
{
	OptimalSolver os;

	cout << "** A-perm **" << endl;
	os.solve("R' F R' B2 R F' R' B2 R2");
	
	cout << "** T-perm **" << endl;
	os.solve("R U R' U' R' F R2 U' R' U' R U R' F'");
	
	cout << "** Y-perm **" << endl;
	os.solve("F R U' R' U' R U R' F' R U R' U' R' F R F'");
	
	cout << "** E-perm **" << endl;
	os.solve("R' U L' D2 L U' R L' U R' D2 R U' L");
	
	cout << "** Z-perm **" << endl;
	os.solve("R U R' U R' U' R' U R U' R' U' R2 U R U2");

	cout << "** Pi-COLL **" << endl;
	os.solve("U2 F U R U' R' U R U2 R' U' R U R' F'");
	
	cout << "** Random (takes way too long) **" << endl;
	os.IDA(vector<int>{ 2, 4, 6, 0, 3, 1, 7, 5 }, vector<int>{ 0, 0, 0, 0, 0, 1, 1, 1 }, vector<int>{ 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1 }, vector<int>{ 4, 9, 1, 2, 8, 7 }, vector<int>{ 3, 11, 10, 5, 6, 0 });
}
