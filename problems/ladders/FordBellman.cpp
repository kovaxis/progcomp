#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll INF = 30000;

struct Edge {
    int u, v;
    ll w;
};

bool bellman_ford(int N, int s, vector<Edge> &E, vector<ll> &D, vector<int> &P) {
    P.assign(N, -1), D.assign(N, INF), D[s] = 0;
    rep(i, N - 1) {
        bool f = true;
        rep(ei, E.size()) {
            auto &e = E[ei];
            ll n = D[e.u] + e.w;
            if (D[e.u] < INF && n < D[e.v]) D[e.v] = n, P[e.v] = ei, f = false;
        }
        if (f) return false;
    }
    return true;
}

int N, M;
vector<Edge> E;
vector<ll> D;
vector<int> P;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    E.resize(M);
    rep(j, M) {
        int u, v, w;
        cin >> u >> v >> w;
        E[j] = {u - 1, v - 1, w};
    }

    bellman_ford(N, 0, E, D, P);

    rep(u, N) cout << D[u] << " \n"[u == N - 1];
}
