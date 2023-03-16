#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> A;
vector<ll> dp(20001, -1);

ll DP(int n) {
    if (dp[n] != -1) {
        return dp[n];
    }

    dp[n] = 1e18;

    for (int i = 1; i <= min(n, int(A.size())); i++) {
        dp[n] = min(dp[n], DP(n - i) + A[i - 1]);
    }

    return dp[n];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    A.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> A[i];
        dp[i + 1] = A[i];
    }

    ll veintemil = 20000;

    dp[0] = 0;

    while (q--) {

        ll x;
        cin >> x;

        ll res = 1e18;
        for (ll i = 1; i <= n; i++) {
            ll div = max(0LL, ((x - veintemil) + (i - 1LL)) / i);
            // cout << "jiji: " << div << "\n";
            res = min(res, DP(x - div * i) + div * A[i - 1]);
        }

        cout << res << "\n";
    }

    return 0;
}