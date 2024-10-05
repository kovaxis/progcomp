#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int N = 16;

bool dp[N][N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    repx(i, 1, N) repx(j, 1, N) repx(k, 1, N) {
        if (i == j || i == k || j == k) continue;
        dp[i][j][k] = true;
        repx(ii, 1, i) if (dp[ii][j][k]) dp[i][j][k] = false;
        repx(jj, 1, j) if (dp[i][jj][k]) dp[i][j][k] = false;
        repx(kk, 1, k) if (dp[i][j][kk]) dp[i][j][k] = false;
    }

    repx(i, 1, N) {
        cout << "map for i = " << i << ":" << endl;
        invrepx(j, 1, N) {
            cout << "  ";
            repx(k, 1, N) cout << dp[i][j][k];
            cout << endl;
        }
    }

    repx(i, 1, N) repx(j, 1, N) repx(k, 1, N) if (!dp[i][j][k]) {
        int stat = i ^ j ^ k;
        cout << i << " " << j << " " << k << ": " << stat << endl;
    }
}
