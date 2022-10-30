#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<vector<int>> G;

int dfs(int u, int p) {
    int cc = 0;
    for (int v : G[u]) cc += (v != p);
    if (cc == 0) return 1;
    if (cc == 1) return 2;
    int mn = 1e9;
    for (int v : G[u])
        if (v != p) mn = min(mn, dfs(v, u));
    return 2 + mn;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        G.assign(N, {});
        rep(i, N - 1) {
            int u, v;
            cin >> u >> v;
            G[u - 1].push_back(v - 1);
            G[v - 1].push_back(u - 1);
        }

        int ans = N - dfs(0, -1);
        cout << ans << "\n";
    }
}
