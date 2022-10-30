#include "../../implementation/dsu.cpp"
#include "../test.h"

struct NDsu {
    int N;
    vector<int> group;

    // initialize the disjoint-set-union to all unitary sets
    void reset(int n) {
        N = n;
        group.resize(N);
        rep(i, N) group[i] = i;
    }

    // find the leader node corresponding to node `i`
    int find(int i) {
        return group[i];
    }

    // perform union on the two sets that `i` and `j` belong to
    void unite(int i, int j) {
        if (i > j) swap(i, j);
        int find = group[j], replace = group[i];
        rep(k, N) if (group[k] == find) group[k] = replace;
    }
};

Dsu re;
NDsu na;

int main() {
    int N = 1e4;
    re.reset(N);
    na.reset(N);
    rep(i, N) {
        int u = random_int(0, N), v = random_int(0, N);
        re.unite(u, v);
        na.unite(u, v);
        rep(j, N) {
            int u = random_int(0, N), v = random_int(0, N);
            assert((re.find(u) == re.find(v)) == (na.find(u) == na.find(v)));
        }
    }
}
