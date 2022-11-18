#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

const ll INF = 1e18;

int N, M, K;
vector<vector<pair<int, ll>>> G;
vector<ll> D, D2;

priority_queue<pair<ll, int>> q;
void dijkstra() {
    rep(i, N) if (D[i] != D2[i]) q.push({-D[i], i});
    while (!q.empty()) {
        ll d = -q.top().first;
        int u = q.top().second;
        q.pop();
        if (d > D[u]) continue;
        for (auto e : G[u]) {
            int v = e.first;
            ll w = e.second;
            if (d + w < D[v]) {
                D[v] = d + w;
                q.push({-D[v], v});
            }
        }
    }
}

void calc_l(int l, int r, int optl, int optr) {
    if (l == r) return;
    int m = (l + r) / 2;
    ll optc = D[m];
    int opti = m;
    repx(i, optl, min(optr, m + 1)) {
        ll c = D[i] + (ll)(m - i) * (m - i);
        if (c < optc) optc = c, opti = i;
    }
    D2[m] = min(D2[m], optc);
    calc_l(l, m, optl, opti + 1);
    calc_l(m + 1, r, opti, optr);
}

void calc_r(int l, int r, int optl, int optr) {
    if (l == r) return;
    int m = (l + r) / 2;
    ll optc = D[m];
    int opti = m;
    repx(i, max(optl, m), optr) {
        ll c = D[i] + (ll)(m - i) * (m - i);
        if (c < optc) optc = c, opti = i;
    }
    D2[m] = min(D2[m], optc);
    calc_r(l, m, optl, opti + 1);
    calc_r(m + 1, r, opti, optr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;
    G.resize(N);
    rep(i, M) {
        ll u, v, w;
        cin >> u >> v >> w;
        G[u - 1].push_back({v - 1, w});
        G[v - 1].push_back({u - 1, w});
    }

    // k = 0
    D2.assign(N, INF);
    D = D2;
    D[0] = 0;
    dijkstra();

    rep(k, K) {
        cerr << "optimal with " << k << " flights:" << endl;
        rep(i, N) cerr << D[i] << " \n"[i == N - 1];
        calc_l(0, N, 0, N);
        calc_r(0, N, 0, N);
        swap(D, D2);
        dijkstra();
    }

    rep(i, N) cout << D[i] << " \n"[i == N - 1];
}
