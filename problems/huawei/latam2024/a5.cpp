#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

struct Edge {
    int v, id;
};

const int N = 50001;
int M;
vector<vector<Edge>> G;
vector<pair<int, int>> E;
vector<vector<int>> ans;

vector<bool> seen;
vector<Edge> P;
vector<int> D;
queue<int> Q;

vector<bitset<N>> basis;
vector<bool> basis_present;

bool add_to_basis(bitset<N> a) {
    rep(j, N) {
        if (!a[j]) continue;
        if (basis_present[j]) {
            a ^= basis[j];
        } else {
            basis[j] = a;
            basis_present[j] = true;
            return true;
        }
    }
    return false;
}

void check_cycle(int root, int u, int v, int id) {
    int w;

    bitset<N> tmpcyc = 0;
    tmpcyc[id] = true;
    w = u;
    while (w != root) {
        tmpcyc[P[w].id] = true;
        w = P[w].v;
    }
    w = v;
    while (w != root) {
        tmpcyc.flip(P[w].id);
        w = P[w].v;
    }

    // cerr << "checking cycle";
    // rep(id, M) if (tmpcyc[id]) cerr << " (" << E[id].first << " " << E[id].second << ")";
    // cerr << endl;

    if (add_to_basis(tmpcyc)) {
        vector<int> nodes;

        w = u;
        while (true) {
            nodes.push_back(w);
            if (w == root || !tmpcyc[P[w].id]) break;
            w = P[w].v;
        }
        reverse(nodes.begin(), nodes.end());
        w = v;
        while (true) {
            nodes.push_back(w);
            if (w == root || !tmpcyc[P[w].id]) break;
            w = P[w].v;
        }

        // cerr << "adding cycle";
        // for (int u : nodes) cerr << " " << u;
        // cerr << endl;

        ans.push_back(nodes);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> M;
    G.assign(N, {});
    E.resize(M);
    rep(id, M) {
        int u, v;
        cin >> u >> v;
        G[u].push_back({v, id});
        G[v].push_back({u, id});
        E[id] = {u, v};
    }

    seen.assign(N, false);
    P.resize(N);
    D.resize(N);
    basis.resize(N);
    basis_present.assign(N, false);

    int components = 0;
    rep(root, N) {
        if (seen[root]) continue;

        seen[root] = true;
        P[root] = {root, -1};
        D[root] = 0;
        Q.push(root);

        if (G[root].empty()) continue;
        components += 1;

        while (Q.size()) {
            int u = Q.front();
            Q.pop();

            for (Edge e : G[u]) {
                if (seen[e.v]) {
                    if (D[e.v] >= D[u]) {
                        // cerr << "loop edge " << u << " " << e.v << endl;
                        check_cycle(root, u, e.v, e.id);
                    }
                } else {
                    seen[e.v] = true;
                    P[e.v] = {u, e.id};
                    D[e.v] = D[u] + 1;
                    Q.push(e.v);
                    // cerr << "new edge " << u << " " << e.v << endl;
                }
            }
        }
    }

    int nonempty_nodes = 0;
    rep(u, N) nonempty_nodes += (G[u].size() > 0);

    cout << ans.size() << "\n";
    for (vector<int> &cyc : ans) {
        cout << cyc.size();
        for (int u : cyc) cout << " " << u;
        cout << "\n";
    }

    cerr << "components: " << components << endl;

    cerr << "got " << ans.size() << "/" << (M - nonempty_nodes + 1) << endl;
}
