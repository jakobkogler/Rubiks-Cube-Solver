#include <iostream>
#include "optimal_solver.h"

int main()
{
    OptimalSolver os(7);

    std::cout << "** Sexy **" << std::endl;
    os.solve("R U R' U'");

    std::cout << "** A-perm **" << std::endl;
    os.solve("R' F R' B2 R F' R' B2 R2");
    
    std::cout << "** T-perm **" << std::endl;
    os.solve("R U R' U' R' F R2 U' R' U' R U R' F'");
    
    std::cout << "** Y-perm **" << std::endl;
    os.solve("F R U' R' U' R U R' F' R U R' U' R' F R F'");
    
    std::cout << "** E-perm **" << std::endl;
    os.solve("R' U L' D2 L U' R L' U R' D2 R U' L");
    
    std::cout << "** Z-perm **" << std::endl;
    os.solve("R U R' U R' U' R' U R U' R' U' R2 U R U2");

    std::cout << "** Pi-COLL **" << std::endl;
    os.solve("U2 F U R U' R' U R U2 R' U' R U R' F'");

    std::cout << "** Random (15 moves) **" << std::endl;
    os.solve("U' B D R2 F' L2 R U' B' D' L B2 F' L2 R'");

    std::cout << "** Random (16 moves) **" << std::endl;
    os.solve("R' L2 D' R' L B2 L2 F D' U F D' L D2 R2 D");
}
