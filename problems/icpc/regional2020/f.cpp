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

int N;
ll num[9000];

// up_to, k
// cost, last_segment_max
pair<ll, ll> dp[9000][9000];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    rep(i, N) cin >> num[i];
    dp[0][0] = {0, 0};
    rep(i, 1, N + 1) dp[i][0] = {INT64_MAX / 8, 0};
    rep(i, 0, N + 1) dp[i][i + 1] = {INT64_MAX / 8, 0};
    rep(i, 1, N + 1) rep(k, 1, i + 1) {
        ll splitmax = num[i - 1];
        pair<ll, ll> split = {dp[i - 1][k - 1].first + splitmax, splitmax};
        ll joinmax = max(dp[i - 1][k].second, splitmax);
        pair<ll, ll> join = {dp[i - 1][k].first - dp[i - 1][k].second + joinmax,
                             joinmax};
        cerr << "i = " << i << ", k = " << k << " has split cost "
             << split.first << " and join cost " << join.first << endl;
        dp[i][k] = min(join, split);
    }
    rep(k, 1, N + 1) cout << dp[N][k].first << " " << 0 << "\n";
}
