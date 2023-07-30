#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (1) cerr

const ll INF = 1e18;

int N, M;
vector<vector<pair<ll, int>>> Gf, Gb;
vector<bool> Mf, Mb;
vector<int> comp;
vector<vector<int>> groups;
vector<bool> has_cycle;
vector<vector<ll>> H;
vector<ll> D;

int mirror(int u) { return (u + N / 2) % N; }

void mark(vector<vector<pair<ll, int>>> &G, vector<bool> &marked, int u) {
    if (marked[u]) return;
    marked[u] = true;
    for (auto [w, v] : G[u]) mark(G, marked, v);
}

bool bford(vector<ll> &D, int i) {
    D.assign(N, INF);
    for (int u : groups[i]) D[u] = 0;
    rep(k, N) {
        bool still = true;
        for (int u : groups[i])
            for (auto [w, v] : Gf[u]) {
                if (D[u] >= INF) continue;
                if (comp[v] != i) continue;
                if (D[u] + w < D[v]) D[v] = D[u] + w, still = false;
            }
        if (still) return false;
    }
    return true;
}

void dijkstra2(vector<ll> &D, int i, int s) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> q;
    D.assign(N, INF);
    D[s] = 0;
    q.push({0, s});
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();
        if (d > D[u]) continue;

        for (auto [w1, v] : Gf[u]) {
            if (comp[v] != i) continue;
            ll w2 = w1 + H[i][u] - H[i][v];
            if (D[u] + w2 < D[v]) D[v] = D[u] + w2, q.push({D[v], v});
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    N *= 2;
    Gf.resize(N), Gb.resize(N);
    rep(j, M) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        int u1 = u, u2 = mirror(u);
        int v1 = v, v2 = mirror(v);
        if ((w % 2 + 2) % 2 == 1) swap(v1, v2);
        Gf[u1].push_back({w, v1});
        Gb[v1].push_back({w, u1});
        Gf[u2].push_back({w, v2});
        Gb[v2].push_back({w, u2});
    }

    comp.assign(N, -1);
    rep(u, N) {
        if (comp[u] != -1) continue;
        Mf.assign(N, false), Mb.assign(N, false);
        mark(Gf, Mf, u);
        mark(Gb, Mb, u);
        int i = groups.size();
        groups.push_back({});
        rep(v, N) if (Mf[v] && Mb[v]) comp[v] = i, groups[i].push_back(v);
    }

    has_cycle.resize(groups.size());
    H.resize(groups.size());
    rep(i, (int)groups.size()) {
        has_cycle[i] = bford(H[i], i);
    }

    rep(u, N / 2) {
        int v = mirror(u);
        int i = comp[u];
        if (comp[v] != comp[u]) {
            cout << "Battle with the crazy Honkai\n";
        } else if (has_cycle[i]) {
            cout << "Haha, stupid Honkai\n";
        } else {
            dijkstra2(D, i, u);
            cout << D[v] - H[i][u] + H[i][v] << "\n";
        }
    }
}