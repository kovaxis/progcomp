#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll INF = 1e18;

struct Edge {
    int u, v;
    ll c, f = 0;
};

// maximum flow algorithm.
//
// time: O(E V^2)
//       O(E V^(2/3)) / O(E sqrt(E))    unit capacities
//       O(E sqrt(V))                   unit networks (hopcroft-karp)
//
// unit network: c in {0, 1} and forall v, len(incoming(v)) <= 1 or len(outgoing(v)) <= 1
//
// min-cut: find all nodes reachable from the source in the residual graph
struct Dinic {
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
        }
        return f;
    }

    vector<bool> cut;
    void mincut(int u) {
        if (cut[u]) return;
        cut[u] = true;
        for (int ei : G[u]) {
            Edge &e = E[ei];
            if (e.c - e.f <= 0) continue;
            mincut(e.v);
        }
    }
    vector<bool> seen;
    void findcut(int u, set<int> &edges) {
        if (seen[u]) return;
        seen[u] = true;
        for (int ei : G[u]) {
            Edge &e = E[ei];
            if (e.c == 0) continue;
            if (cut[e.v]) findcut(e.v, edges);
            else edges.insert(ei);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;
    Dinic flow(N, 0, N - 1);
    rep(j, M) {
        int u, v;
        cin >> u >> v;
        u -= 1, v -= 1;
        flow.add_edge(u, v, 1);
        flow.add_edge(v, u, 1);
    }
    flow.maxflow();
    flow.cut.assign(N, false);
    flow.mincut(0);
    flow.seen.assign(N, false);
    set<int> cut;
    flow.findcut(0, cut);
    cout << cut.size() << "\n";
    for (int ei : cut) cout << flow.E[ei].u + 1 << " " << flow.E[ei].v + 1 << "\n";
}
