#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

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

int N, K;
vector<int> Cbase, C;
map<pair<int, int>, int> Ebase, E;
vector<pair<int, int>> ans_e;
int ans_root;

int classify(int x) {
    x += 1;
    int c = 0;
    while (x) c += 1, x /= 10;
    return c - 1;
}

bool is_valid_tree(vector<int> P) {
    int cnt = 0, root;
    rep(u, K) {
        if (P[u] == u) {
            root = u;
            cnt += 1;
        }
    }
    if (cnt != 1) return false;

    rep(u, K) {
        int v = u;
        rep(iter, K + 1) {
            v = P[v];
        }
        if (v != root) return false;
    }

    return true;
}

bool attach(int i, int j) {
    if (C[j] <= 0) return false;
    C[j] -= 1;
    if (E[make_pair(min(i, j), max(i, j))] <= 0) return false;
    E[make_pair(min(i, j), max(i, j))] -= 1;
    ans_e.push_back({i, j});
    return true;
}

bool attach_base(vector<vector<int>> &G, int i) {
    for (int j : G[i]) {
        if (!attach(i, j)) return false;
        if (!attach_base(G, j)) return false;
    }
    return true;
}

bool try_basetree(vector<int> P) {
    if (!is_valid_tree(P)) return false;
    ans_e.clear();

    E = Ebase;
    C = Cbase;

    int root;
    rep(i, K) {
        if (P[i] == i) root = i;
    }
    if (C[root] <= 0) return false;
    C[root] -= 1;
    ans_root = root;

    vector<vector<int>> G(K);
    rep(i, K) if (P[i] != i) G[P[i]].push_back(i);
    if (!attach_base(G, root)) return false;

    // [0, K) classes
    // [K, K+E.size()) aristas
    // [K+E.size()) s
    // [K+E.size()+1) t
    int s = K + E.size(), t = K + E.size() + 1;
    Dinic flow(K + E.size() + 2, s, t);

    int id = 0;
    for (auto [tipo, cnt] : E) {
        auto [i, j] = tipo;
        flow.add_edge(s, K + id, cnt);
        flow.add_edge(K + id, i, INF);
        flow.add_edge(K + id, j, INF);
        id += 1;
    }
    rep(k, K) {
        flow.add_edge(k, t, C[k]);
    }

    ll f = flow.maxflow();
    ll wantflow = 0;
    for (auto [tipo, cnt] : E) wantflow += cnt;

    if (f != wantflow) return false;

    vector<pair<int, int>> id2ij;
    for (auto [tipo, cnt] : E) {
        id2ij.push_back(tipo);
    }

    for (auto &e : flow.E) {
        if (e.f > 0 && e.u >= K && e.u < K + E.size()) {
            int j = e.v;
            int id = e.u - K;
            int i;
            if (id2ij[id].first != j) i = id2ij[id].first;
            else i = id2ij[id].second;
            rep(times, e.f) {
                if (!attach(i, j)) return false;
            }
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    rep(i, N - 1) {
        string u, v;
        cin >> u >> v;
        int uu = u.size() - 1, vv = v.size() - 1;
        if (uu > vv) swap(uu, vv);
        Ebase[make_pair(uu, vv)] += 1;
    }

    K = classify(N - 1) + 1;
    Cbase.resize(K);
    rep(i, N) {
        Cbase[classify(i)] += 1;
    }

    // try all base trees
    vector<int> P(K, 0);
    while (true) {
        if (try_basetree(P)) {
            break;
        }

        bool quit = true;
        rep(i, K) {
            P[i] += 1;
            if (P[i] >= K) {
                P[i] = 0;
            } else {
                quit = false;
                break;
            }
        }
        if (quit) {
            cout << "-1" << endl;
            return 0;
        }
    }

    vector<vector<int>> unused(K), used(K);
    rep(i, N) {
        unused[classify(i)].push_back(i + 1);
    }

    used[ans_root].push_back(unused[ans_root].back());
    unused[ans_root].pop_back();

    for (auto [i, j] : ans_e) {
        // cerr << "connecting class "<<i<<" to class "<< j << endl;
        int u = used[i].back();
        int v = unused[j].back();
        unused[j].pop_back();
        used[j].push_back(v);

        cout << u << " " << v << "\n";
    }
}