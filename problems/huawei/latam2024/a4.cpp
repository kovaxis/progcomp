#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= int(a); i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (1) cerr

struct Edge {
    int v, id;
};

const int N = 50001;
int M;
vector<vector<Edge>> G;
vector<Edge> P;
vector<pair<int, int>> E;
vector<int> D;
vector<bool> seen;
queue<int> Q;
vector<vector<int>> ans;

vector<bitset<N>> basis;
vector<int> basis_pivots;

bitset<N> tmpcyc;

bool add_to_basis(bitset<N> &a) {
    int i = 0;
    rep(j, N) {
        if (!a[j]) continue;
        while (i < (int)basis.size() && basis_pivots[i] < j) i += 1;
        if (i < (int)basis.size() && basis_pivots[i] == j) {
            a ^= basis[i];
        } else {
            // place here
            basis.insert(basis.begin() + i, a);
            basis_pivots.insert(basis_pivots.begin() + i, j);
            return true;
        }
    }
    return false;
}

/*
int gauss(vector<vector<double>> a, vector<double> &ans) {
    int N = a.size(), M = a[0].size() - 1;

    vector<int> where(M, -1);
    for (int j = 0, i = 0; j < M && i < N; j++) {
        int sel = i;
        repx(k, i, N) if (abs(a[k][j]) > abs(a[sel][j])) sel = k;
        if (abs(a[sel][j]) < EPS) continue;
        repx(k, j, M + 1) swap(a[sel][k], a[i][k]);
        where[j] = i;

        rep(k, N) if (k != i) {
            double c = a[k][j] / a[i][j];
            repx(l, j, M + 1) a[k][l] -= a[i][l] * c;
        }
        i++;
    }

    ans.assign(M, 0);
    rep(i, M) if (where[i] != -1) ans[i] = a[where[i]][M] / a[where[i]][i];
    rep(i, N) {
        double sum = 0;
        rep(j, M) sum += ans[j] * a[i][j];
        if (abs(sum - a[i][M]) > EPS) return 0;
    }

    rep(i, M) if (where[i] == -1) return -1;
    return 1;
}
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> M;
    G.resize(N);
    E.resize(M);
    rep(id, M) {
        int u, v;
        cin >> u >> v;
        G[u].push_back({v, id});
        G[v].push_back({u, id});
        E[id] = {u, v};
        if (u == v) {
            while (true) {
                cerr << "alo" << endl;
            }
        }
    }

    P.resize(N), D.resize(N), seen.assign(N, false);
    int roots = 0;
    rep(root, N) {
        if (seen[root] || G[root].empty()) continue;
        cerr << "root at " << root << endl;
        roots += 1;
        Q.push(root);
        seen[root] = true;
        P[root] = {root, -1};

        while (Q.size()) {
            int u = Q.front();
            Q.pop();
            for (Edge e : G[u]) {
                if (seen[e.v]) {
                    // loop
                    if (D[e.v] > D[u] || (D[u] == D[e.v] && u < e.v)) {
                        // cerr << "edge from " << u << " to " << v << " is a loop" << endl;
                        tmpcyc = 0;
                        tmpcyc[e.id] = 1;
                        vector<int> from_u;
                        int uu = u;
                        while (uu != root) {
                            from_u.push_back(uu);
                            tmpcyc.flip(P[uu].id);
                            uu = P[uu].v;
                        }
                        vector<int> from_v;
                        int vv = e.v;
                        while (vv != root) {
                            from_v.push_back(vv);
                            tmpcyc.flip(P[vv].id);
                            vv = P[vv].v;
                        }

                        cerr << "checking cycle through loop edge " << u << " " << e.v << endl;
                        cerr << "  includes edges";
                        rep(id, M) if (tmpcyc[id]) cerr << " (" << E[id].first << " " << E[id].second << ")";
                        cerr << endl;

                        if (add_to_basis(tmpcyc)) {
                            int last = root;
                            while (from_u.size() && from_v.size() && from_u.back() == from_v.back()) last = from_u.back(), from_u.pop_back(), from_v.pop_back();
                            from_u.push_back(last);
                            from_v.push_back(last);
                            reverse(from_u.begin(), from_u.end());
                            from_u.insert(from_u.end(), from_v.begin(), from_v.end());
                            ans.push_back(from_u);
                        }
                    }
                } else {
                    cerr << "edge from " << u << " to " << e.v << " is new" << endl;
                    Q.push(e.v);
                    P[e.v] = {u, e.id};
                    D[e.v] = D[u] + 1;
                    seen[e.v] = true;
                }
            }
        }
    }

    cout << ans.size() << "\n";
    for (auto &cyc : ans) {
        cout << cyc.size();
        for (int u : cyc) cout << " " << u;
        cout << "\n";
    }

    if (roots > 1) {
        cerr << "disconnected graph!" << endl;
    }
    int v = 0;
    rep(u, N) v += (G[u].size() != 0);
    cerr << "got " << ans.size() << "/" << (M - v + 1) << endl;
}
