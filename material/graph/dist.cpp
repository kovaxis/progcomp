#include "../common.h"

const ll INF = 1e18;

// calculate distances between every pair of nodes in O(n^3) time and O(n^2)
// memory.
// requires an NxN array to store results.
void floyd(const vector<vector<pair<int, ll>>>& G, vector<vector<ll>>& dists) {
    int N = G.size();
    rep(i, N) rep(j, N) dists[i][j] = i == j ? 0 : INF;
    rep(i, N) for (auto edge : G[i]) dists[i][edge.first] = edge.second;
    rep(k, N) rep(i, N) rep(j, N) {
        dists[i][j] = min(dists[i][j], dists[i][k] + dists[k][j]);
    }
}

// calculate shortest distances from a source node to every other node in
// O(m log n). requires an array of size N to store results.
void dijkstra(const vector<vector<pair<int, ll>>>& G, vector<ll>& dists,
              int src) {
    dists.assign(G.size(), INF);
    dists[src] = 0;
    priority_queue<pair<ll, int>> q;
    q.push({0, src});
    while (!q.empty()) {
        ll d = q.top().first;
        int v = q.top().second;
        q.pop();
        if (d > dists[v]) continue;
        for (auto edge : G[v]) {
            int to = edge.first;
            ll w = edge.second;
            if (d + w < dists[to]) {
                dists[to] = d + w;
                q.push({dists[to], to});
            }
        }
    }
}

#ifndef NOMAIN_DIST

int main() {}

#endif
