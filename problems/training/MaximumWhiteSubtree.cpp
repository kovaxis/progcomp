#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<int> a;
vector<vector<int>> G;

vector<int> dp1;
int dfs1(int u, int p) {
    int res = a[u];
    for (int v : G[u]) {
        if (v == p) continue;
        res += max(0, dfs1(v, u));
    }
    return dp1[u] = res;
}

vector<int> dp2;
void dfs2(int u, int p) {
    int res = dp1[u];
    if (p != -1) res += max(0, dp2[p] - max(0, dp1[u]));
    dp2[u] = res;

    for (int v : G[u]) {
        if (v == p) continue;
        dfs2(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    a.resize(N), G.resize(N);
    rep(i, N) cin >> a[i];
    rep(i, N) a[i] = a[i] * 2 - 1;
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        G[u - 1].push_back(v - 1);
        G[v - 1].push_back(u - 1);
    }

    dp1.resize(N), dp2.resize(N);
    dfs1(0, -1), dfs2(0, -1);

    rep(i, N) cout << dp2[i] << " \n"[i == N - 1];
}
