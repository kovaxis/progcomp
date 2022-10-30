#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int W, H;

vector<vector<bool>> a;
vector<vector<int>> dp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> H >> W;
    a.assign(W, vector<bool>(H));
    rep(y, H) rep(x, W) {
        char c;
        cin >> c;
        a[x][y] = (c == 'G');
    }

    dp.resize(W, vector<int>(H));
    rep(x, W) rep(y, H) {
        if (x == 0 || y == 0) {
            dp[x][y] = 1;
            continue;
        }
        int res = 1;
        if (a[x][y] == a[x - 1][y]) {
            if (a[x][y - 1] == a[x - 1][y - 1]) res = 2;
            int sub = min(min(dp[x - 1][y], dp[x - 1][y - 1]), dp[x][y - 1]);
            if (sub >= 2) res = sub + 1;
        }
        dp[x][y] = res;
    }

    int ans = 0;
    rep(x, W) rep(y, H) ans = max(ans, dp[x][y]);
    cout << ans * ans << endl;
}
