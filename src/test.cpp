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

    cout << "** Random (15 moves) **" << endl;
    os.solve("U' B D R2 F' L2 R U' B' D' L B2 F' L2 R'");

    cout << "** Random (16 moves) **" << endl;
    os.solve("R' L2 D' R' L B2 L2 F D' U F D' L D2 R2 D");
}
