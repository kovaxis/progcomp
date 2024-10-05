#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (1) cerr

struct Edge {
    int u, v;
    int rev;
    bool bridge;
};

// calculates the lowest common ancestor for any two nodes in O(log N) time,
// with O(N log N) preprocessing
struct Lca {
    int N, K, t = 0;
    vector<vector<int>> U;
    vector<int> L, R;

    Lca() {}
    Lca(vector<vector<Edge>> &G) : N(G.size()), L(N), R(N) {
        K = N <= 1 ? 0 : 32 - __builtin_clz(N - 1);
        U.resize(K + 1, vector<int>(N));
        visit(G, 0, 0);
        rep(k, K) rep(u, N) U[k + 1][u] = U[k][U[k][u]];
    }

    void visit(vector<vector<Edge>> &G, int u, int p) {
        L[u] = t++, U[0][u] = p;
        for (Edge e : G[u])
            if (e.bridge)
                if (e.v != p) visit(G, e.v, u);
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

int N, M, C;
vector<vector<Edge>> G;
vector<int> comp, S;
vector<ll> Sacc;
Lca lca;

int bridgeTn;
vector<int> bridgeT;
int find_bridges(int u, int p) {
    if (bridgeT[u] != -1) return bridgeT[u];
    bridgeT[u] = bridgeTn++;
    int ss = bridgeT[u];
    for (Edge &e : G[u])
        if (e.v != p) {
            int s = find_bridges(e.v, u);
            if (s <= bridgeT[u]) {
                e.bridge = false;
                G[e.v][e.rev].bridge = false;
            }
            ss = min(ss, s);
        }
    return ss;
}

int find_components(int u) {
    if (comp[u] != -1) return false;
    comp[u] = C;
    for (Edge e : G[u])
        if (!e.bridge) {
            find_components(e.v);
            S[C] += 1;
        }
    return true;
}

void accumulate(int u, int p) {
    Sacc[u] += Sacc[p];
    Sacc[u] += S[u];
    for (Edge e : G[u])
        if (e.v != p && e.bridge) accumulate(e.v, u);
}

ll answer(int u, int v) {
    int w = lca.find(u, v);
    return Sacc[u] + Sacc[v] - 2 * Sacc[w] + S[w];
}

int main() {
    cin >> N >> M;
    G.resize(N);
    rep(j, M) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int ui = G[u].size(), vi = G[v].size();
        G[u].push_back({u, v, vi, true});
        G[v].push_back({v, u, ui, true});
    }

    // find bridges
    bridgeT.resize(N, -1);
    bridgeTn = 0;
    find_bridges(0, -1);

    // find components and their sizes
    comp.resize(N, -1), S.resize(2 * N), C = N;
    rep(u, N) C += find_components(u);
    rep(c, C) S[c] /= 2;

    // add a virtual node per component and connect it to the port nodes
    G.resize(C);
    rep(u, N) {
        int c = comp[u];
        G[u].push_back({u, c, -1, true});
        G[c].push_back({c, u, -1, true});
    }

    // accumulate on paths
    Sacc.resize(C);
    accumulate(0, 0);

    // build lca
    lca = {G};

    // process queries
    int Q;
    cin >> Q;
    rep(q, Q) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        cout << answer(u, v) << "\n";
    }
}
