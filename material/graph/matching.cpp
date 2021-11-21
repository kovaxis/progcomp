#include "../common.h"

vector<bool> seen;
vector<int> mt;

bool subkuhn(vector<vector<int>>& adj, int i) {
    if (seen[i]) return false;
    seen[i] = true;
    for (int to : adj[i])
        if (mt[to] == -1 || subkuhn(adj, mt[to])) {
            mt[to] = i;
            return true;
        }
    return false;
}

// get a maximum matching out of a **bipartite** graph.
// returns the size of the matching (ie. the covered vertices).
// runs in O(n * m) time.
int kuhn(vector<vector<int>>& adj) {
    int N = adj.size(), total = 0;
    mt.assign(N, -1);
    rep(i, N) {
        seen.assign(N, -1);
        total += subkuhn(adj, i);
    }
    return total;
}

#ifndef NOMAIN_MATCHING

int main() {}

#endif
