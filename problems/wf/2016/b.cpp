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
    int v, w;
};

int GN, N, K, GM;
vector<vector<Edge>> G, G2;
vector<ll> C, acc;
vector<pair<ll, int>> dp;

void dijkstra() {
    priority_queue<pair<ll, int>> q;
    vector<ll> D(GN, INF);
    D[N] = 0;
    q.push({0, N});
    while(q.size()) {
        auto [d, u] = q.top();
        d = -d;
        q.pop();
        if (d > D[u]) continue;

        for(Edge e : G[u]) {
            if (D[u] + e.w < D[e.v]) {
                D[e.v] = D[u] + e.w;
                q.push({-D[e.v], e.v});
            }
        }
    }
    rep(u, N) C[u] += D[u];
}

pair<ll, int> solve(ll C) {
    dp.resize(N+1);
    dp[0] = {0, 0};
    rep(i, N) {
        pair<ll, int> mn = {INF, -1};
        rep(j, i+1) {
            ll c = dp[j].first + (acc[i+1] - acc[j]) * (i - j) + C;
            pair<ll, int> res = {c, dp[j].second + 1};
            mn = min(mn, res);
        }
        dp[i+1] = mn;
    }
    return dp[N];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> GN >> N >> K >> GM;
    G.resize(GN);
    G2.resize(GN);
    rep(j, GM) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        G[u].push_back({v, w});
        G2[v].push_back({u, w});
    }

    C.resize(N);
    dijkstra();
    swap(G, G2);
    dijkstra();

    sort(C.begin(), C.end());

    acc.resize(N+1);
    rep(i, N) acc[i+1] = acc[i] + C[i];

    ll l = 0, r = 1e15;
    while(l != r) {
        ll m = (l+r)/2;
        auto [c, k] = solve(m);
        if (k <= K) {
            r = m;
        }else{
            l = m + 1;
        }
    }

    ll ans = solve(l).first - K * l;

    cout << ans << endl;
}
