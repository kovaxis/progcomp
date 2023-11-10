#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > 0;)
#define invrep(i, n) invrepx(i, 0, n)

const int INF = 1e9;

struct Lca {
    int N, K, t = 0;
    vector<vector<int>> U;
    vector<int> L, R, D;

    Lca() {}
    Lca(vector<vector<int>> &G) : N(G.size()), L(N), R(N) {
        K = N <= 1 ? 0 : 32 - __builtin_clz(N - 1);
        U.resize(K + 1, vector<int>(N)), D.assign(N, 0);
        visit(G, 0, 0);
        rep(k, K) rep(u, N) U[k + 1][u] = U[k][U[k][u]];
    }

    void visit(vector<vector<int>> &G, int u, int p) {
        L[u] = t++, U[0][u] = p;
        for (int v : G[u])
            if (v != p) D[v] = D[u] + 1, visit(G, v, u);
        R[u] = t++;
    }

    bool is_anc(int up, int dn) {
        return L[up] <= L[dn] && R[dn] <= R[up];
    }

    int find(int u, int v) {
        if (is_anc(u, v)) return u;
        if (is_anc(v, u)) return v;
        for (int k = K; k >= 0;)
            if (is_anc(U[k][u], v)) k--;
            else u = U[k][u];
        return U[0][u];
    }
};

int N, B;
vector<vector<int>> G;
vector<bool> painted;
vector<pair<int, int>> down, both;
vector<int> pending, ans;
Lca lca;

void dpdown(int u, int p) {
    for (int v : G[u])
        if (v != p) {
            dpdown(v, u);
        }

    if (painted[u]) {
        down[u] = {0, u};
        return;
    }

    for (int v : G[u])
        if (v != p) {
            auto sub = down[v];
            sub.first += 1;
            down[u] = min(down[u], sub);
        }
}

void dpup(int u, int p) {
    auto super = both[p];
    super.first += 1;
    both[u] = min(down[u], super);

    for (int v : G[u])
        if (v != p) {
            dpup(v, u);
        }
}

void recompute() {
    // cerr << "recomputing" << endl;
    down.resize(N), both.resize(N);
    rep(u, N) down[u] = {INF, u}, both[u] = {INF, u};

    dpdown(0, 0);
    // cerr << "  down:";
    // rep(u, N) cerr << down[u].first << "," << down[u].second + 1 << " ";
    // cerr << endl;
    dpup(0, 0);
    // cerr << "  both:";
    // rep(u, N) cerr << both[u].first << "," << both[u].second + 1 << " ";
    // cerr << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    G.resize(N);
    rep(j, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    painted.assign(N, false);
    lca = {G};
    B = sqrt(N);
    ans.resize(N);
    recompute();
    invrep(u, N) {
        // cerr << "answering query for " << u + 1 << endl;
        auto dist = both[u];
        for (int v : pending) {
            pair<int, int> d = {lca.D[u] + lca.D[v] - 2 * lca.D[lca.find(u, v)], v};
            // cerr << "  distance against pending " << v + 1 << ": " << d.first << "," << d.second + 1 << endl;
            dist = min(dist, d);
        }
        ans[u] = dist.second;

        pending.push_back(u);
        painted[u] = true;
        if ((int)pending.size() >= B) {
            recompute();
            pending.clear();
        }
    }

    rep(u, N) cout << ans[u] + 1 << " ";
    cout << endl;
}
