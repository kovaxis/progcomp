#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll INF = 1e18;

struct Dinic {
    struct Edge {
        int u, v;
        ll c, f = 0;
        int id = -1;
    };
    int N, s, t;
    vector<vector<int>> G;
    vector<Edge> E;
    vector<int> lvl, ptr;
    Dinic() {}
    Dinic(int N, int s, int t) : N(N), s(s), t(t), G(N) {}

    void add_edge(int u, int v, ll c, int id = -1) {
        G[u].push_back(E.size());
        E.push_back({u, v, c, 0, id});
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

int N, M, Qn, Nl, Nr;
vector<pair<int, int>> E;
vector<vector<int>> G;
vector<int> mate, matv;
vector<bool> rebalsa;
set<int> norebalsa;
ll esum;

void setrebalsa(int u) {
    if (rebalsa[u]) return;
    rebalsa[u] = true;
    norebalsa.erase(u);
    for (int v : G[u]) {
        if (matv[v] != -1) {
            setrebalsa(matv[v]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> Nl >> Nr;
    N = Nl + Nr;
    cin >> M >> Qn;
    G.resize(N);
    rep(j, M) {
        int u, v;
        cin >> u >> v;
        u -= 1, v -= 1;
        v += Nl;
        E.push_back({u, v});
        G[u].push_back(v);
        G[v].push_back(u);
    }

    Dinic flow(N + 2, N, N + 1);
    rep(u, Nl) flow.add_edge(N, u, 1);
    rep(v, Nr) flow.add_edge(Nl + v, N + 1, 1);
    rep(id, M) flow.add_edge(E[id].first, E[id].second, 1, id);
    flow.maxflow();

    mate.assign(N, -1), matv.assign(N, -1);
    for (auto e : flow.E) {
        if (e.id != -1 && e.f > 0) {
            auto [u, v] = E[e.id];
            mate[u] = e.id, mate[v] = e.id;
            matv[u] = v, matv[v] = u;
            esum += e.id + 1;
        }
    }

    rebalsa.assign(N, false);
    rep(u, N) norebalsa.insert(u);
    rep(u, N) if (matv[u] == -1) setrebalsa(u);

    rep(qi, Qn) {
        int qty;
        cin >> qty;
        if (qty == 1) {
            // remove
            int u = *norebalsa.begin();
            int v = matv[u];
            norebalsa.erase(u);
            esum -= mate[u] + 1;
            matv[u] = -1, mate[u] = -1;
            matv[v] = -1, mate[v] = -1;
            setrebalsa(v);
            cout << "1\n";
            cout << (u < Nl ? u + 1 : -(u - Nl + 1)) << "\n";
            cout << esum << endl;
        } else {
            // print
            int sz = 0;
            rep(u, Nl) if (mate[u] != -1) sz += 1;
            cout << sz << "\n";
            rep(u, Nl) if (mate[u] != -1) cout << mate[u] + 1 << " ";
            cout << endl;
        }
    }
}
