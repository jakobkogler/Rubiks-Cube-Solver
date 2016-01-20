#ifndef RUBIKS_CUBE_SOLVER_COLLISIONSET_H
#define RUBIKS_CUBE_SOLVER_COLLISIONSET_H

#include<vector>

using namespace std;

class Collisionset {
private:
    vector<char> data;
    long long mod;

public:
    Collisionset(long long size, long long mod);
    void add(long long item);
    bool contains(long long item);
};

#endif //RUBIKS_CUBE_SOLVER_COLLISIONSET_H
