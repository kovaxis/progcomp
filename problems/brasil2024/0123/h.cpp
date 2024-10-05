#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll INF = 1e18;

struct Kuhn {
    vector<vector<int>> G;
    int N, size = 0;
    vector<bool> seen;
    vector<int> mt;

    bool visit(int i) {
        if (seen[i]) return false;
        seen[i] = true;
        for (int to : G[i])
            if (mt[to] == -1 || visit(mt[to])) {
                mt[to] = i;
                return true;
            }
        return false;
    }

    Kuhn(vector<vector<int>> adj) : G(adj), N(G.size()), mt(N, -1) {
        rep(i, N) {
            seen.assign(N, false);
            size += visit(i);
        }
    }
};

struct Dinic {
    struct Edge {
        int u, v;
        ll c, f = 0;
    };
    int N, s, t;
    vector<vector<int>> G;
    vector<Edge> E;
    vector<int> lvl, ptr;
    Dinic(int N = 0, int s = 0, int t = 0) : N(N), s(s), t(t), G(N) {}

    void add_edge(int u, int v, ll c) {
        G[u].push_back(E.size());
        E.push_back({u, v, c});
        G[v].push_back(E.size());
        E.push_back({v, u, 0});
    }

    ll push(int u, ll p) {
        if (u == t || p <= 0) return p;
        while (ptr[u] < G[u].size()) {
            int ei = G[u][ptr[u]++];
            Edge &e = E[ei];
            if (lvl[e.v] != lvl[u] + 1) continue;
            ll a = push(e.v, min(e.c - e.f, p));
            if (a <= 0) continue;
            e.f += a, E[ei ^ 1].f -= a;
            return a;
        }
        return 0;
    }

    ll maxflow() {
        ll f = 0;
        while (true) {
            lvl.assign(N, -1);
            queue<int> q;
            lvl[s] = 0;
            q.push(s);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int ei : G[u]) {
                    Edge &e = E[ei];
                    if (e.c - e.f <= 0 || lvl[e.v] != -1) continue;
                    lvl[e.v] = lvl[u] + 1;
                    q.push(e.v);
                }
            }
            if (lvl[t] == -1) break;
            ptr.assign(N, 0);
            while (ll ff = push(s, INF)) f += ff;
        }
        return f;
    }
};

int N;
vector<vector<int>> S;
vector<int> C, R, L;
vector<bool> chosen;
vector<vector<int>> residual;

void dfs(int u) {
    if (chosen[u]) return;
    chosen[u] = true;
    for (int v : residual[u]) {
        dfs(v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    S.resize(N);
    rep(i, N) {
        int n;
        cin >> n;
        S[i].resize(n);
        rep(j, n) cin >> S[i][j];
        rep(j, n) S[i][j] -= 1;
    }
    C.resize(N);
    rep(i, N) cin >> C[i];

    vector<vector<int>> G(2 * N);
    rep(i, N) for (int x : S[i]) {
        // cerr << "connecting " << i << " and " << N + x << endl;
        G[i].push_back(N + x);
        G[N + x].push_back(i);
    }
    Kuhn match(G);

    R.resize(N), L.resize(N);
    rep(i, N) {
        R[i] = match.mt[i] - N;
        L[i] = match.mt[N + i];
    }

    Dinic cut(N + 2, N, N + 1);
    rep(i, N) {
        if (C[i] > 0) {
            cut.add_edge(i, N + 1, C[i]);
        } else if (C[i] < 0) {
            cut.add_edge(N, i, -C[i]);
        }
    }
    rep(i, N) {
        for (int x : S[i])
            if (L[x] != i) {
                cut.add_edge(i, L[x], INF);
            }
    }
    cut.maxflow();

    residual.resize(N + 2);
    for (auto &e : cut.E) {
        if (e.f < e.c) {
            residual[e.u].push_back(e.v);
        }
    }
    chosen.resize(N + 2);
    dfs(N);

    int ans = 0;
    rep(i, N) {
        if (chosen[i]) ans += C[i];
    }

    cout << ans << endl;
}
