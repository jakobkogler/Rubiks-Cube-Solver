#include "Collisionset.h"

Collisionset::Collisionset(long long size, long long mod) {
    data = vector<char>((size + 7) / 8);
    this->mod = mod;
}

void Collisionset::add(long long item) {
    long long idx = item % mod;
    data[idx / 8] |= 1 << (idx % 8);
}

bool Collisionset::contains(long long item) {
    long long idx = item % mod;
    return data[idx / 8] & (1 << idx % 8);
}
