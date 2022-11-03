#include "../common.h"

const ll INF = 1e18;

// calculate shortest distances from a source node to every other node in
// O(E log V). requires an array of size N to store results.
void dijkstra(const vector<vector<pair<int, ll>>> &G, vector<ll> &D, int src) {
    D.assign(G.size(), INF);
    D[src] = 0;
    priority_queue<pair<ll, int>> q;
    q.push({0, src});
    while (!q.empty()) {
        ll d = -q.top().first;
        int u = q.top().second;
        q.pop();
        if (d > D[u]) continue;
        for (auto e : G[u]) {
            int v = e.first;
            ll w = e.second;
            if (d + w < D[v]) {
                D[v] = d + w;
                q.push({-D[v], v});
            }
        }
    }
}
