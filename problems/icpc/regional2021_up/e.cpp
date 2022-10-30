#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll INF = 1e18;

int N;
vector<ll> sail, dive, fix;

// dp[start][end] = max cost to fix if at start and failing segment is between
// start and end (inclusive). start might be larger than end, indicating that
// the boat is currently at the end of the segments instead of at the start.
ll dpmem[4096][4096];

ll dp(int i, int j) {
    if (dpmem[i][j] != -1) return dpmem[i][j];
    if (i == j) return dpmem[i][j] = fix[i];
    ll dist = 0, mincost = INF;
    int l = min(i, j), r = max(i, j);
    int dir = (i < j ? 1 : -1), off = (i < j ? 1 : 0);
    rep(kk, r - l) {
        int k = i + (off + kk) * dir;
        // diagnose repeater `k`
        dist += sail[k - off];
        ll cost = dist + dive[k] + max(dp(k - 1, l), dp(k, r));
        mincost = min(mincost, cost);
    }
    return dpmem[i][j] = mincost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    sail.resize(N + 1), dive.resize(N + 1), fix.resize(N + 1);
    repx(i, 1, N) cin >> sail[i];
    repx(i, 1, N + 1) cin >> dive[i];
    repx(i, 0, N + 1) cin >> fix[i];

    rep(i, N + 1) rep(j, N + 1) dpmem[i][j] = -1;
    cout << dp(0, N) << endl;
}
