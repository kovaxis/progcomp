#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, ans;
vector<vector<int>> G;
vector<ll> L, R;

ll dfs(int u) {
    ll cap = 0;
    for (int v : G[u]) cap += dfs(v);
    if (cap < L[u]) cap = R[u], ans += 1;
    return min(cap, R[u]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        G.assign(N, {}), L.resize(N), R.resize(N);
        repx(i, 1, N) {
            int p;
            cin >> p;
            G[p - 1].push_back(i);
        }
        rep(i, N) cin >> L[i] >> R[i];

        ans = 0;
        dfs(0);
        cout << ans << "\n";
    }
}
