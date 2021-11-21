// https://codeforces.com/contest/1550/problem/E

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int N, K, ans;
string s;

int nxt_block[17][200002];

int dp[1 << 17];

int minsubstr(int mask) {
    if (dp[mask] != -1) return dp[mask];
    int min_n = mask == 0 ? 0 : N + 1;
    rep(k, K) if (mask & (1 << k)) {
        int submask = mask & ~(1 << k);
        min_n = min(min_n, nxt_block[k][minsubstr(submask)]);
    }
    // cerr << "minsubstr for mask ";
    // rep(k, K) cerr << ((mask >> k) & 1);
    // cerr << " = " << min_n << endl;
    return dp[mask] = min_n;
}

bool works() {
    // cerr << "checking answer " << ans << endl;

    int last_ltr = -1, first_ltr = -1, first_ltridx = -1;
    int idx[K];
    rep(k, K) idx[k] = 0;
    rep(i, N) {
        if (s[i] != '?') {
            if (first_ltr == -1 || s[i] != first_ltr) {
                first_ltridx = last_ltr + 1;
                first_ltr = s[i];
            }
            last_ltr = i;
        }
        if (i - last_ltr >= ans) {
            // cerr << "setting wildcardly up to " << i - ans + 1 << " to "
            //     << i + 1 << endl;
            rep(k, K) while (idx[k] <= i - ans + 1) nxt_block[k][idx[k]++] =
                i + 1;
        }
        if (first_ltr != -1 && i - first_ltridx + 1 >= ans) {
            int k = first_ltr - 'a';
            // cerr << "setting '" << (char)first_ltr << "' up to " << i - ans +
            // 1
            //     << " to " << i + 1 << endl;
            while (idx[k] <= i - ans + 1) nxt_block[k][idx[k]++] = i + 1;
        }
    }
    rep(k, K) while (idx[k] <= N + 1) nxt_block[k][idx[k]++] = N + 1;

    /*rep(k, K) {
        cerr << (char)('a' + k) << ":";
        rep(i, N + 2) cerr << " " << nxt_block[k][i];
        cerr << endl;
    }*/

    rep(i, 1 << K) dp[i] = -1;
    return minsubstr((1 << K) - 1) <= N;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K >> s;

    int l = 1, r = N / K + 1;
    while (l != r) {
        ans = l + (r - l) / 2;
        if (works()) {
            l = ans + 1;
        } else {
            r = ans;
        }
    }
    cout << l - 1 << endl;
}
