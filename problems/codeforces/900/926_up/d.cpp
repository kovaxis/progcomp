#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int MOD = 998244353;

int N;
vector<vector<int>> G;

pair<int, int> dfs(int u, int p) {
    int rmul = 1, fsum = 0, rsum = 0;
    for (int v : G[u])
        if (v != p) {
            auto [sr, sf] = dfs(v, u);
            rmul = (ll)rmul * sr % MOD;
            fsum = (fsum + sf) % MOD;
            rsum = ((ll)rsum + sr - 1 + MOD) % MOD;
        }
    int r = (1 + rmul) % MOD;
    int f = (fsum + rsum) % MOD;
    return {r, f};
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

        auto [r, f] = dfs(0, -1);
        cout << (r + f) % MOD << "\n";
    }
}
