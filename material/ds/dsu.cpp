#include "../common.h"

struct Dsu {
    vector<int> p, r;

    Dsu() {}
    // initialize the disjoint-set-union to all unitary sets
    void reset(int N) {
        p.resize(N), r.assign(N, 0);
        rep(i, N) p[i] = i;
    }

    // find the leader node corresponding to node `i`
    int find(int i) {
        if (p[i] != i) p[i] = find(p[i]);
        return p[i];
    }

    // perform union on the two disjoint sets with leaders `i` and `j`
    // note: `i` and `j` must be LEADERS OF TWO SEPARATE SETS
    int unite(int i, int j) {
        if (r[i] > r[j]) {
            p[j] = i;
            return j;
        } else {
            if (r[i] == r[j]) r[j] += 1;
            p[i] = j;
            return i;
        }
    }
};

#ifndef NOMAIN_DSU

Dsu ufind;
vector<int> expected;

void unite(int u, int v, vector<int> ex) {
    cerr << "joining " << u << " and " << v << endl;
    u = ufind.find(u - 1);
    v = ufind.find(v - 1);
    if (u != v) ufind.unite(u, v);
    rep(i, ufind.p.size()) cerr << ufind.find(i) + 1 << " ";
    cerr << endl;
    rep(i, ex.size()) assert(ex[i] - 1 == ufind.find(i));
}

int main() {
    ufind.resize(10);
    expected.resize(10);
    rep(i, 10) expected[i] = i;
    unite(1, 8, {8, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    unite(3, 9, {8, 2, 9, 4, 5, 6, 7, 8, 9, 10});
    unite(10, 2, {8, 2, 9, 4, 5, 6, 7, 8, 9, 2});
    unite(3, 7, {8, 2, 9, 4, 5, 6, 9, 8, 9, 2});
    unite(1, 4, {8, 2, 9, 8, 5, 6, 9, 8, 9, 2});
    unite(4, 5, {8, 2, 9, 8, 8, 6, 9, 8, 9, 2});
    unite(10, 9, {8, 9, 9, 8, 8, 6, 9, 8, 9, 9});
    unite(3, 3, {8, 9, 9, 8, 8, 6, 9, 8, 9, 9});
    unite(1, 9, {9, 9, 9, 9, 9, 6, 9, 9, 9, 9});
}

#endif
