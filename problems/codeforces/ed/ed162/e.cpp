#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<int> C;
vector<vector<int>> G;
ll ans;

map<int, int> dfs(int u, int p) {
    int c = C[u];
    map<int, int> all;
    for (int v : G[u])
        if (v != p) {
            map<int, int> sub = dfs(v, u);
            ans += (ll)sub[c] * (sub[c] - 1) / 2;
            ans += sub[c];
            if (sub.size() > all.size()) swap(sub, all);
            for (auto [k, v] : sub) all[k] += v;
        }
    all[c] = 1;
    return all;
}

ll solve() {
    ans = 0;
    map<int, int> see = dfs(0, -1);
    for (auto [c, n] : see) {
        ans += (ll)n * (n - 1) / 2;
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
        C.resize(N);
        rep(u, N) cin >> C[u];
        G.assign(N, {});
        rep(j, N - 1) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            G[u].push_back(v);
            G[v].push_back(u);
        }

        cout << solve() << "\n";
    }
}
