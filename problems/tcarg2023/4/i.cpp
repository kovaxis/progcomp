#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

int N, M;
vector<vector<int>> G;
vector<int> Gb;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    G.resize(N);
    rep(j, M) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    Gb.resize(N);
    rep(u, N) {
        for (int v : G[u]) Gb[u] |= 1 << v;
    }

    int mn = N;
    int mn_m = (1 << N) - 1;
    rep(m, 1 << N) {
        // check that all nodes have an active neighbor or are connected to everything
        int ok = m;
        rep(u, N) if (Gb[u] & m) ok |= 1 << u;
        rep(u, N) if (((1 << u) | Gb[u]) == (1 << N) - 1) ok |= 1 << u;
        if (ok != (1 << N) - 1) continue;

        // check that the bitmask is connected
        if (m) {
            int q = 1 << __builtin_ctz(m);
            int seen = q;
            while (q) {
                int u = __builtin_ctz(q);
                q &= ~(1 << u);
                int adj = m & Gb[u] & ~(seen);
                q |= adj;
                seen |= adj;
            }
            if (seen != m) continue;
        }

        cerr << "mask " << m << " works" << endl;

        int cnt = __builtin_popcount(m);
        if (cnt < mn) mn = cnt, mn_m = m;
    }

    cout << mn << endl;
    rep(u, N) if ((1 << u) & mn_m) cout << u + 1 << " ";
    cout << endl;
}
