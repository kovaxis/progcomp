#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<vector<pair<int, ll>>> G;
vector<ll> a;
vector<bool> rem;

void dfs(int u, ll d) {
    rem[u] = (d > a[u]);
    for (auto p : G[u]) {
        dfs(p.first, max(0ll, d + p.second));
    }
}

int dfs2(int u) {
    if (rem[u]) return 0;
    // cerr << "keeping " << u + 1 << endl;
    int cnt = 1;
    for (auto p : G[u]) {
        cnt += dfs2(p.first);
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    a.resize(N), G.resize(N), rem.resize(N);
    rep(i, N) cin >> a[i];
    rep(i, N - 1) {
        ll p, c;
        cin >> p >> c;
        G[p - 1].push_back({i + 1, c});
    }

    dfs(0, 0);
    int ans = N - dfs2(0);
    cout << ans << endl;
}
