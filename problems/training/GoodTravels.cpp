#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Scc {
    int vn, N;
    vector<int> order, comp;
    vector<vector<int>> vg, vgi, G;

    void toposort(int u) {
        if (comp[u]) return;
        comp[u] = -1;
        for (int v : vg[u]) toposort(v);
        order.push_back(u);
    }

    bool carve(int u) {
        if (comp[u] != -1) return false;
        comp[u] = N;
        for (int v : vgi[u]) {
            carve(v);
            if (comp[v] != N) G[comp[v]].push_back(N);
        }
        return true;
    }

    Scc() {}
    Scc(vector<vector<int>> &g) : vn(g.size()), vg(g) {
        // toposort
        comp.resize(vn);
        rep(u, vn) toposort(u);

        // transpose
        vgi.resize(vn);
        rep(u, vn) for (int v : vg[u]) vgi[v].push_back(u);

        G.resize(vn), N = 0;
        invrep(i, vn) N += carve(order[i]);
    }
};

int N, M, S, E;
vector<ll> a, b;
vector<vector<int>> G;
Scc scc;

vector<ll> dp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> S >> E;
    S--, E--;
    a.resize(N), G.resize(N);
    rep(u, N) cin >> a[u];
    rep(j, M) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
    }

    scc = Scc(G);
    b.resize(scc.N);
    rep(u, N) b[scc.comp[u]] += a[u];

    dp.resize(scc.N);
    invrep(c, scc.N) {
        dp[c] = -1e18;
        for (int v : scc.G[c]) dp[c] = max(dp[c], dp[v]);
        if (scc.comp[E] == c) dp[c] = 0;
        dp[c] += b[c];
        // cerr << "dp[";
        // rep(u, N) if (scc.comp[u] == c) cerr << u + 1 << " ";
        // cerr << "] = " << dp[c] << endl;
    }

    cout << dp[scc.comp[S]] << endl;
}
