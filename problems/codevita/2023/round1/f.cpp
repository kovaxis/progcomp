#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (1) cerr

ll solve(string s, string perm) {
    cerr << "trying order " << perm << endl;
    int invk[128];
    rep(k, 4) invk[perm[k]] = k;

    int dp[4];
    rep(k, 4) dp[k] = 0;
    rep(i, (int)s.size()) {
        int newdp[4];
        rep(k, 4) newdp[k] = 1e9;
        rep(kdst, 4) rep(ksrc, 4) {
            if (kdst < ksrc) continue; // only allow going forward in stages
            int cost = dp[ksrc];
            if (kdst < invk[s[i]]) {
                // send character backward
                cost += 1;
            } else if (kdst > invk[s[i]]) {
                // send character forward
                cost += 1;
            } else {
                // place character right here
            }
            newdp[kdst] = min(newdp[kdst], cost);
        }
        rep(k, 4) {
            dp[k] = newdp[k];
            cerr << "  dp[" << i + 1 << "][" << perm[k] << "] = " << dp[k] << endl;
        }
    }

    int res = 1e9;
    rep(k, 4) res = min(res, dp[k]);
    cerr << "  " << res << " swaps" << endl;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    string A(N, ' ');
    rep(i, N) cin >> A[i];

    string perm = "HSPD";
    ll ans = 1e18;
    do {
        ans = min(ans, solve(A, perm));
    } while (next_permutation(perm.begin(), perm.end()));

    cout << ans << endl;
}
