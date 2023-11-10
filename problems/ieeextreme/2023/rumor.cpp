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
    Scc(vector<vector<int>> &g) : vn(g.size()), vg(g), comp(vn), vgi(vn), G(vn), N(0) {
        rep(u, vn) toposort(u);
        rep(u, vn) for (int v : vg[u]) vgi[v].push_back(u);
        invrep(i, vn) N += carve(order[i]);
    }
};

int N, M;
unordered_map<string, int> mapping;
vector<string> antimap;
vector<vector<int>> G;

int conv(string name) {
    if (mapping.count(name)) return mapping[name];
    antimap.push_back(name);
    G.push_back({});
    return mapping[name] = N++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> M;
    rep(j, M) {
        string a, op, b;
        cin >> a >> op >> b;
        int u = conv(a), v = conv(b);
        G[u].push_back(v);
        if (op == "??") {
            G[v].push_back(u);
        }
    }

    Scc scc(G);
    vector<int> indeg(scc.N);
    for (vector<int> adj : scc.G) {
        for (int v : adj) indeg[v] += 1;
    }
    vector<string> answer;
    rep(u, N) {
        if (indeg[scc.comp[u]] == 0) {
            answer.push_back(antimap[u]);
        }
    }
    sort(answer.begin(), answer.end());
    for (string &n : answer) cout << n << "\n";
}
