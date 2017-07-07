#include <iostream>
#include "optimal_solver.h"
#include "kociemba_solver.h"

using namespace std;

struct Scramble
{
    std::string name;
    std::string moves;
};

int main()
{
    KociembaSolver ks;
    OptimalSolver os;

    std::vector<Scramble> scrambles = {
        { "Sexy", "R U R' U'"}, 
        { "A-perm", "R' F R' B2 R F' R' B2 R2" },
        { "T-perm", "R U R' U' R' F R2 U' R' U' R U R' F'" },
        { "Y-perm", "F R U' R' U' R U R' F' R U R' U' R' F R F'" }, 
        { "E-perm", "R' U L' D2 L U' R L' U R' D2 R U' L" },
        { "Z-perm", "R U R' U R' U' R' U R U' R' U' R2 U R U2" },
        { "Pi-COLL", "U2 F U R U' R' U R U2 R' U' R U R' F'" }, 
        { "Random (15 moves)", "U' B D R2 F' L2 R U' B' D' L B2 F' L2 R'" }, 
        { "Random (16 moves)", "R' L2 D' R' L B2 L2 F D' U F D' L D2 R2 D" }
    };
    
    for (auto scramble : scrambles) {
        cout << "** " << scramble.name << " **" << endl;
        ks.solve(scramble.moves);
        os.solve(scramble.moves);
    }
}
