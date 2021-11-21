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

struct Node {
    int period;
    int nxt;
};

int dp[4000009];

Node nodes[4000009];
int divlist[4000009];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    int mod;
    cin >> n >> mod;

    rep(i, 2, n + 1) {
        nodes[i] = {i, -1};
        divlist[i] = i;
    }

    dp[1] = 1;
    int acc = 1;
    int div_acc = 0;
    rep(i, 2, n + 1) {
        // cerr << "  " << acc << " subtractive ways\n";
        int idx = divlist[i];
        while (idx != -1) {
            int period = nodes[idx].period;
            int nxt = nodes[idx].nxt;
            // cerr << "  dividing " << i << " by " << period
            //     << " yields " << i / period << "\n";
            div_acc =
                ((div_acc + dp[i / period]) % mod + mod - dp[i / period - 1]) %
                mod;
            if (i + period <= n) {
                nodes[idx].nxt = divlist[i + period];
                divlist[i + period] = idx;
            }
            idx = nxt;
        }
        // cerr << "  " << div_acc << " divisive ways\n";
        int ways = (acc + div_acc) % mod;
        // cerr << ways << " ways to reach 1 from cell " << i << "\n";
        dp[i] = ways;
        acc = (acc + ways) % mod;
    }
    cout << dp[n] << '\n';
}
