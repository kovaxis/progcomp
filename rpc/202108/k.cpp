#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

const ll INF = 1e14;

int N;
vector<pair<int, ll>> adj[100001];
ll dists[100001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int M;
    cin >> N >> M;
    rep(m, M) {
        int u, v, t;
        cin >> u >> v >> t;
        adj[u - 1].push_back({v - 1, t});
        adj[v - 1].push_back({u - 1, t});
    }

    dists[0] = 0;
    rep(i, 1, N) dists[i] = INF;
    set<pair<ll, int>> q;
    q.insert({0, 0});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());

        for (auto edge : adj[v]) {
            int to = edge.first;
            ll len = edge.second;

            if (dists[v] + len < dists[to]) {
                q.erase({dists[to], to});
                dists[to] = dists[v] + len;
                q.insert({dists[to], to});
            }
        }
    }
    ll cost = 0;
    rep(i, N) cost = max(cost, dists[i]);
    cout << cost << endl;
}
