#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, M;
ll K;
vector<int> A;
vector<vector<int>> G, iG;

vector<ll> DP;
ll dp(int u) {
    if (DP[u] != -1) return DP[u];
    ll len = 0;
    for (int v : G[u])
        if (A[v] < A[u]) {
            len = max(len, dp(v) + K - (A[u] - A[v]));
        } else {
            len = max(len, dp(v) + (A[v] - A[u]));
        }
    return DP[u] = len;
}

ll solve() {
    DP.assign(N, -1);

    ll end = 0;
    rep(i, N) end = max(end, A[i] + dp(i));

    vector<int> byA(N);
    rep(i, N) byA[i] = i;
    sort(byA.begin(), byA.end(), [](int i, int j) {
        return A[i] < A[j];
    });

    ll ans = 1e18;
    for (int i : byA) {
        ans = min(ans, end - A[i]);
        end = max(end, A[i] + K + dp(i));
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> M >> K;
        A.resize(N), G.assign(N, {}), iG.assign(N, {});
        rep(i, N) cin >> A[i];
        rep(j, M) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            G[u].push_back(v);
            iG[v].push_back(u);
        }

        cout << solve() << "\n";
    }
}
