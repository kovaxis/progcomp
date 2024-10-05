#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Euler {
    struct Edge {
        int v, rev;
        int id;
        bool isrev;
    };

    int N;
    vector<vector<Edge>> G;
    vector<Edge> P;

    Euler(int N = 0) : N(N), G(N) {}

    void add_edge(int u, int v, int id) {
        G[u].push_back({v, (int)G[v].size(), id, false});
        G[v].push_back({u, (int)G[u].size() - 1, id, true});
    }

    void go(int u) {
        while (G[u].size()) {
            Edge e = G[u].back();
            G[u].pop_back();
            if (e.v == -1) continue;
            G[e.v][e.rev].v = -1;
            go(e.v);
            P.push_back(e);
        }
    }

    vector<Edge> getpath(int u) {
        return P.clear(), go(u), reverse(P.begin(), P.end()), P;
    }
};

int N;
vector<int> color;

int trunc(int i, int B) {
    return color[i] & ((1 << B) - 1);
}

bool solve(int B) {
    Euler G(1 << B);
    rep(j, N) {
        int a = trunc(2 * j, B), b = trunc(2 * j + 1, B);
        G.add_edge(a, b, j);
    }

    rep(u, 1 << B) if (G.G[u].size() % 2 != 0) return false;

    vector<Euler::Edge> path;
    int root = -1;
    rep(u, 1 << B) {
        root = u;
        path = G.getpath(u);
        if (path.size()) break;
    }
    assert(path.size());

    if (path.size() != N) return false;
    if (path.back().v != root) return false;

    cout << B << endl;
    for (auto e : path) {
        int i1 = 2 * e.id, i2 = 2 * e.id + 1;
        if (e.isrev) swap(i1, i2);
        cout << i1 + 1 << " " << i2 + 1 << " ";
    }
    cout << endl;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    color.resize(2 * N);
    rep(i, 2 * N) cin >> color[i];

    invrep(b, 21) {
        if (solve(b)) break;
    }
}
