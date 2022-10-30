#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

const ll MOD = 1000000007;

int N, K;
ll L;
ll kmatrix[751][751];
int parr[10001];

// pos, k
// accumulated_count
ll dp[10001][751];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> K >> L;
    rep(i, K) rep(j, K) cin >> kmatrix[i][j];
    cin >> N;
    rep(i, N - 1) cin >> parr[i];
    rep(k, K + 1) { dp[N - 1][k] = k; }
    invrep(i, N - 1) {
        ll p = parr[i];
        ll acc = 0;
        dp[i][0] = 0;
        rep(k, K) {
            int lo =
                lower_bound(kmatrix[k], kmatrix[k] + K, p - L) - kmatrix[k];
            int hi =
                upper_bound(kmatrix[k], kmatrix[k] + K, p + L) - kmatrix[k];
            ll count = (dp[i + 1][hi] + MOD - dp[i + 1][lo]) % MOD;
            acc = (acc + count) % MOD;
            dp[i][k + 1] = acc;
        }
    }
    cout << dp[0][K] << endl;
}
