#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

// nitrogen, oxygen, tanks
// complete, weight
pair<bool, int> dp[22][80][1001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int ts;
    cin >> ts;
    rep(t, ts) {
        int tn, to, tc;
        cin >> tn >> to >> tc;
        rep(n, tn + 1) {
            rep(o, to + 1) { dp[n][o][0] = {false, 0}; }
        }
        dp[0][0][0] = {true, 0};
        rep(i, 1, tc + 1) {
            int cn, co, cw;
            cin >> cn >> co >> cw;
            rep(n, tn + 1) {
                rep(o, to + 1) {
                    auto& keep = dp[n][o][i - 1];
                    auto& add = dp[max(n - cn, 0)][max(o - co, 0)][i - 1];
                    int addw = add.second + cw;
                    if (!keep.first || addw < keep.second) {
                        dp[n][o][i] = {add.first, addw};
                    } else {
                        dp[n][o][i] = keep;
                    }
                }
            }
        }
        cout << dp[tn][to][tc].second << '\n';
    }
}
