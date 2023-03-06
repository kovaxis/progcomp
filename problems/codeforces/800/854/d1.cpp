#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

int N, K;
vector<int> a;
vector<ll> hot, cold;

vector<vector<ll>> dp;

const ll INF = 1e17;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> K;
        a.resize(N);
        cold.resize(K), hot.resize(K);
        rep(i, N) cin >> a[i];
        rep(i, N) a[i] -= 1;
        rep(k, K) cin >> cold[k];
        rep(k, K) cin >> hot[k];

        // dp[n][k] = minimum time of running programs [0, n], and finishing with programs a[n] and k in the cache
        // dp[n][K] = minimum time of running programs [0, n], and finishing with a[n] and any other in the cache
        dp.assign(N, vector<ll>(K + 1, INF));
        dp[0][a[0]] = cold[a[0]];
        dp[0][K] = dp[0][a[0]];
        repx(n, 1, N) {
            rep(k, K) {
                if (k == a[n] || k == a[n - 1]) {
                    dp[n][k] = min(dp[n - 1][a[n]] + hot[a[n]], dp[n - 1][K] + cold[a[n]]);
                } else {
                    dp[n][k] = dp[n - 1][k] + (a[n - 1] == a[n] ? hot[a[n]] : cold[a[n]]);
                }
                cerr << "dp[" << n + 1 << "][" << k + 1 << "] = " << dp[n][k] << endl;
                dp[n][K] = min(dp[n][K], dp[n][k]);
            }
            cerr << "dp[" << n + 1 << "][?] = " << dp[n][K] << endl;
        }

        cout << dp[N - 1][K] << "\n";
    }
}
