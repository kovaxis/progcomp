#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<int> a(N);
    rep(i, N) cin >> a[i];

    vector<ll> pow2(N + 1, 1);
    rep(i, N) pow2[i + 1] = pow2[i] * 2 % MOD;

    // dp[n] = sum over all subsets with >= 2 elements, containing element n
    vector<ll> dp(N);

    rep(n, N) {
        int mirror = n;
        ll res = 0;
        invrep(i, n) {
            while (mirror > 0 && a[i] - a[mirror] < a[n] - a[i]) mirror -= 1;
            res += dp[i];
            res += pow2[mirror];
            cerr << "  mirror of " << i << " and " << n << " is " << mirror << endl;
            res %= MOD;
        }
        dp[n] = res;
        cerr << "dp[" << n << "] = " << dp[n] << endl;
    }

    ll ans = 0;
    rep(i, N) ans = (ans + dp[i]) % MOD;

    cout << ans << endl;
}
