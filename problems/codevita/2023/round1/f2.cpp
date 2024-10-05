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

int solve(const string &s, const string &perm) {
    int dp[4];
    rep(k, 4) dp[k] = 0;

    rep(i, (int)s.size()) {
        int sk = -1;
        rep(k, 4) if (perm[k] == s[i]) sk = k;
        assert(sk != -1);

        int newdp[4];
        rep(k, 4) {
            newdp[k] = dp[0];
            rep(ksrc, k + 1) newdp[k] = min(newdp[k], dp[ksrc]);

            if (sk != k) newdp[k] += 1;
        }

        rep(k, 4) dp[k] = newdp[k];
    }

    int ans = dp[0];
    rep(k, 4) ans = min(ans, dp[k]);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    string s(N, ' ');
    rep(i, N) {
        char c;
        cin >> c;
        s[i] = c;
    }

    string perm = "DHPS";
    int ans = 1e9;
    do {
        ans = min(ans, solve(s, perm));
    } while (next_permutation(perm.begin(), perm.end()));

    cout << ans << endl;
}
