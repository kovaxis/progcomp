// 6A

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

const ll INF = 1e18;

struct Dinic {
    struct Edge {
        int u, v;
        ll c, f = 0;
    };

    int N, s, t;
    vector<vector<int>> G;
    vector<Edge> E;
    vector<int> lvl, ptr;

    Dinic() {}
    Dinic(int N, int s, int t) : N(N), s(s), t(t), G(N) {}

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
            // bfs to build levels
            lvl.assign(N, -1);
            queue<int> q;
            lvl[s] = 0, q.push(s);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int ei : G[u]) {
                    Edge &e = E[ei];
                    if (e.c - e.f <= 0 || lvl[e.v] != -1) continue;
                    lvl[e.v] = lvl[u] + 1, q.push(e.v);
                }
            }
            if (lvl[t] == -1) break;

            // dfs to find blocking flow
            ptr.assign(N, 0);
            while (ll ff = push(s, INF)) f += ff;
            if (f >= INF) return INF;
        }
        return f;
    }
};

struct Constr {
    int t;
    pair<int, int> endpoints[2];
};

int N, M, Q;
vector<vector<int>> G;
vector<int> A;
vector<Constr> C;

ll solve(int qv, int i) {
    cerr << "  minimizing bit " << i << endl;

    // s = 0, t = 1
    int s = N, t = N + 1;
    Dinic flow(N + 2, s, t);

    rep(u, N) if (A[u] != -1) {
        if (A[u] & (1 << i)) {
            cerr << "    forced node " << u << " to 1" << endl;
            flow.add_edge(u, t, INF);
        } else {
            cerr << "    forced node " << u << " to 0" << endl;
            flow.add_edge(s, u, INF);
        }
    }

    rep(q, Q) {
        rep(k, 2) {
            auto [u, j] = C[q].endpoints[k];
            if (j != i) continue;
            int x = (qv >> q) & 1;
            if (C[q].t && k) x ^= 1;
            if (x) {
                cerr << "    forced node " << u << " to 1 from restriction " << q << endl;
                flow.add_edge(u, t, INF);
            } else {
                cerr << "    forced node " << u << " to 0 from restriction " << q << endl;
                flow.add_edge(s, u, INF);
            }
        }
    }

    rep(u, N) for (int v : G[u]) {
        cerr << "    cutting " << u << " and " << v << " has cost 1" << endl;
        flow.add_edge(u, v, 1);
    }

    return flow.maxflow();
}

int main() {
    cin >> N >> M;
    G.resize(N);
    rep(j, M) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    A.resize(N);
    rep(i, N) cin >> A[i];
    cin >> Q;
    C.resize(Q);
    rep(q, Q) {
        int t, u, i, v, j;
        cin >> t >> u >> i >> v >> j;
        C[q] = {t, {{u, i}, {v, j}}};
    }

    vector<vector<ll>> res(16, vector<ll>(1 << Q));
    rep(i, 16) {
        int m = 0;
        rep(q, Q) rep(k, 2) {
            auto [u, j] = C[q].endpoints[k];
            if (i == j) m |= 1 << q;
        }
        int qv = m;
        while (true) {
            ll ans = solve(qv, i);
            res[i][qv] = ans;

            if (qv == 0) break;
            qv = (qv - 1) & m;
        }
        rep(qv, 1 << Q) {
            res[i][qv] = res[i][qv & m];
        }
    }

    ll ans = INF;
    rep(qv, 1 << Q) {
        ll partial = 0;
        rep(i, 16) partial = min(partial + res[i][qv], INF);
        ans = min(ans, partial);
    }
    if (ans == INF) ans = -1;
    cout << ans << endl;
}
