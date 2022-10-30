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

int n;
// col, row
int balls[1001][1001];
// col, granted_rows
// max_score
long long dp[1001][1001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }
        rep(row, n) {
            rep(col, row + 1) {
                cin >> balls[col][row - col];
                if (row - col > 0) {
                    balls[col][row - col] += balls[col][row - col - 1];
                }
            }
        }
        /*cout << "sumstack:" << endl;
        rep(row, n) {
            rep(col, n - row) { cout << balls[col][row] << " "; }
            cout << endl;
        }*/
        rep(col, n) {
            long long highest = -999999999999999999ll;
            invrep(rows, n - col + 1) {
                long long score =
                    (col <= 0 ? 0ll : dp[col - 1][rows]) +
                    (rows <= 0 ? 0ll : (long long)balls[col][rows - 1]);
                if (score > highest) {
                    highest = score;
                }
                dp[col][rows] = highest;
            }
        }
        cout << dp[n - 1][0] << '\n';
    }
}
