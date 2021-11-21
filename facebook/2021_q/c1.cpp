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

vector<ll> gold;
vector<ll> maxgold;
vector<vector<int>> adj;

ll traverse(int i, int p) {
    ll maxg = 0;
    for (int child : adj[i]) {
        if (child == p) continue;
        maxg = max(maxg, traverse(child, i));
    }
    return maxgold[i] = maxg + gold[i];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        int N;
        cin >> N;
        gold.resize(N);
        maxgold.clear();
        maxgold.resize(N);
        adj.clear();
        adj.resize(N);
        rep(i, N) cin >> gold[i];
        rep(i, N - 1) {
            int u, v;
            cin >> u >> v;
            adj[u - 1].push_back(v - 1);
            adj[v - 1].push_back(u - 1);
        }
        traverse(0, 0);
        ll maxg = gold[0];
        rep(i, adj[0].size()) rep(j, i + 1) {
            ll g = maxgold[adj[0][i]] + (i == j ? 0 : maxgold[adj[0][j]]) +
                   gold[0];
            maxg = max(maxg, g);
        }
        cout << "Case #" << t + 1 << ": " << maxg << "\n";
    }
}
