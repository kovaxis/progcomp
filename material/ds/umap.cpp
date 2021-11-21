#include "../common.h"

// hackproof rng
static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// deterministic rng
uint64_t splitmix64(uint64_t* x) {
    uint64_t z = (*x += 0x9e3779b97f4a7c15);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    return z ^ (z >> 31);
}

// hackproof unordered map hash
struct Hash {
    size_t operator()(const ll& x) const {
        static const uint64_t RAND =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t z = x + RAND + 0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }
};

// hackproof unordered_map
template <class T, class U>
using umap = unordered_map<T, U, Hash>;

// hackproof unordered_set
template <class T>
using uset = unordered_set<T, Hash>;

#ifndef NOMAIN_UMAP

int main() {
    umap<int, int> umap;

    umap.insert({3, 5});
    umap.insert({-4, 10});
    cout << "3: " << umap[3] << endl;
    cout << "-5: " << umap[-5] << endl;
    cout << "-4: " << umap[-4] << endl;
}

#endif
