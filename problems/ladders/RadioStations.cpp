// https://codeforces.com/problemset/problem/1215/F
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
    vector<vector<int>> *vg;
    vector<vector<int>> vgi;

    void toposort(int u) {
        if (comp[u]) return;
        comp[u] = -1;
        for (int v : (*vg)[u]) toposort(v);
        order.push_back(u);
    }

    bool carve(int u) {
        if (comp[u] != -1) return false;
        comp[u] = N;
        for (int v : vgi[u]) {
            carve(v);
        }
        return true;
    }

    Scc() {}
    Scc(vector<vector<int>> &g) : vn(g.size()), vg(&g), comp(vn), vgi(vn), N(0) {
        rep(u, vn) toposort(u);
        rep(u, vn) for (int v : (*vg)[u]) vgi[v].push_back(u);
        invrep(i, vn) N += carve(order[i]);
    }
};

struct TwoSat {
    int N;
    vector<vector<int>> G;
    Scc scc;
    vector<bool> sol;

    TwoSat() {}
    TwoSat(int n) : N(n), G(2 * n), sol(n), scc(G) {}

    int neg(int u) { return (u + N) % (2 * N); }
    void then(int u, int v) { G[u].push_back(v), G[neg(v)].push_back(neg(u)); }
    void any(int u, int v) { then(neg(u), v); }
    void set(int u) { G[neg(u)].push_back(u); }

    bool solve() {
        scc = Scc(G);
        rep(u, N) if (scc.comp[u] == scc.comp[neg(u)]) return false;
        rep(u, N) sol[u] = (scc.comp[u] > scc.comp[neg(u)]);
        return true;
    }
};

int need_n, radio_n, M, conflict_n;
vector<pair<int, int>> radios;
TwoSat sat;

int radio(int i) {
    return i;
}

int acc(int m) {
    return radio_n + m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> need_n >> radio_n >> M >> conflict_n;
    sat = TwoSat(radio_n + M + 1);
    rep(i, need_n) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        sat.any(radio(u), radio(v));
    }
    radios.resize(radio_n);
    rep(i, radio_n) {
        int l, r;
        cin >> l >> r;
        l--;
        radios[i] = {l, r};
    }
    rep(i, conflict_n) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        sat.any(sat.neg(radio(u)), sat.neg(radio(v)));
    }

    rep(m, M) sat.then(acc(m), acc(m + 1));

    rep(i, radio_n) {
        sat.then(radio(i), acc(radios[i].second));
        sat.any(sat.neg(radio(i)), sat.neg(acc(radios[i].first)));
    }

    if (!sat.solve()) {
        cout << "-1\n";
        return 0;
    }

    int f = M;
    invrep(m, M + 1) {
        if (sat.sol[acc(m)]) f = m;
    }

    vector<int> ans;
    rep(i, radio_n) if (sat.sol[radio(i)]) ans.push_back(i);

    cout << ans.size() << " " << f << "\n";
    rep(i, ans.size()) cout << ans[i] + 1 << " \n"[i == ans.size() - 1];
}
