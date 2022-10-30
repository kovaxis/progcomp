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

int n, globk;
int first[35001][101];
int last[35001];
// up_to, k
// cost, last_seg_start
pair<int, int> dp[35001][101];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> globk;
    rep(i, n) {
        rep(k, globk) { first[i][k] = -1; }
        last[i] = -1;
    }
    rep(k, globk) { dp[0][k] = {0, 0}; }
    rep(i, 1, n + 1) {
        int x;
        cin >> x;
        x -= 1;

        rep(k, globk) {
            int costnew = k == 0 ? 0 : dp[i - 1][k - 1].first;
            int costmerge = dp[i - 1][k].first;
            // compute first relative to dp[i-1][k].second !
            if (first[x][k] >= dp[i - 1][k].second) {
                costmerge -= last[x] - first[x][k];
                costmerge += i - first[x][k];
            } else {
                first[x][k] = i;
            }
            if (k != 0 && costnew <= costmerge) {
                // split
                dp[i][k] = {costnew, i};
                first[x][k] = i;
            } else {
                // merge
                dp[i][k] = {costmerge, dp[i - 1][k].second};
            }
        }
        last[x] = i;
    }
    cout << dp[n][globk - 1].first << '\n';
}
