#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, M;
int H[7][7];
int isrc, jsrc, idst, jdst;

int DP[101][7][7];
int dp(int h, int i, int j) {
    if (h > 100 || i < 0 || i >= N || j < 0 || j >= M) return 1e9;
    if (DP[h][i][j] != -1) return DP[h][i][j];
    int mx = h, cnt = 1;
    repx(i2, i - 1, i + 2) repx(j2, j - 1, j + 2) {
        if (i2 == i && j2 == j) continue;
        if (H[i2][j2] > mx) mx = H[i2][j2], cnt = 0;
        if (H[i2][j2] >= mx) cnt += 1;
    }
    int res = 1e9;
    repx(i2, i - 1, i + 2) repx(j2, j - 1, j + 2) {
        if (i2 == i && j2 == j) continue;
        int cost;
        if (H[i2][j2] == mx && cnt == 1) cost = dp(mx, i2, j2);
        else cost = dp(mx + 1, i2, j2) + mx + 1 - H[i2][j2];
        res = min(res, cost);
    }
    // cerr << "dp[" << h << "][" << i + 1 << "][" << j + 1 << "] = " << res << endl;
    return DP[h][i][j] = res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    rep(i, N) rep(j, M) cin >> H[i][j];
    cin >> isrc >> jsrc;
    cin >> idst >> jdst;
    isrc--, jsrc--, idst--, jdst--;
    rep(h, 101) rep(i, N) rep(j, M) DP[h][i][j] = -1;
    repx(h, H[idst][jdst], 101) DP[h][idst][jdst] = 0;
    cout << dp(H[isrc][jsrc], isrc, jsrc) << endl;
}
