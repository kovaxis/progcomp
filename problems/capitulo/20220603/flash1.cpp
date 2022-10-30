#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, M, S, D;
ll T;

vector<vector<pair<int, ll>>> G;
vector<bool> seen;

bool haspath(ll trips) {
    ll mincap = (T + trips - 1) / trips;
    seen.assign(N, false);
    return dfs(0, false);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    rep(i, M) {
        ll p;
        int u, v;
        cin >> u >> v >> p;
        G[u - 1].push_back({v - 1, p - 1});
        G[v - 1].push_back({u - 1, p - 1});
    }
    cin >> S >> D >> T;

    ll l = 1, r = T;
    while (l != r) {
        int m = (l + r) / 2;
        if (haspath(m)) {
            l = m + 1;
        } else {
            r = m;
        }
    }
}
