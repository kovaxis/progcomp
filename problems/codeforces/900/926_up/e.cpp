#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, K;
vector<vector<int>> G;
vector<pair<int, int>> AB;
vector<int> P, B, D;
vector<vector<int>> tops;
vector<int> order;

void dfs(int u, int p, int d) {
    D[u] = d;
    P[u] = p;
    for (int v : G[u])
        if (v != p) {
            dfs(v, u, d + 1);
        }
}

bool dfspath(int u, int p, int k) {
    if (u == AB[k].second) return true;
    for (int v : G[u])
        if (v != p) {
            if (dfspath(v, u, k)) {
                if (P[u] == v) B[u] |= (1 << k);
                else B[v] |= (1 << k);
                return true;
            }
        }
    return false;
}

int solve() {
    P.resize(N);
    D.assign(N, 0);
    dfs(0, -1, 0);

    B.assign(N, 0);
    rep(k, K) dfspath(AB[k].first, -1, k);

    tops.assign(K, {});
    rep(k, K) rep(u, N) if (P[u] != -1 && (B[u] & (1 << k))) {
        if (tops[k].empty() || D[tops[k][0]] > D[u]) tops[k].clear();
        if (tops[k].empty() || D[tops[k][0]] == D[u]) tops[k].push_back(u);
    }
    rep(k, K) if (tops[k].size() == 1) tops[k].push_back(tops[k][0]);

    order.resize(K);
    rep(k, K) order[k] = k;
    sort(order.begin(), order.end(), [](int k1, int k2) {
        return D[tops[k1][0]] > D[tops[k2][0]];
    });

    int ans = K;
    rep(m, 1 << K) {
        int done = 0;
        int cost = 0;
        for (int k : order) {
            if (done & (1 << k)) continue;
            int u = tops[k][(m >> k) & 1];
            done |= B[u];
            cost += 1;
        }
        ans = min(ans, cost);
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        G.assign(N, {});
        rep(j, N - 1) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        cin >> K;
        AB.resize(K);
        rep(k, K) cin >> AB[k].first >> AB[k].second;
        rep(k, K) AB[k].first--, AB[k].second--;

        cout << solve() << "\n";
    }
}
