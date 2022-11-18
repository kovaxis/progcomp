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

ll board[2][100002];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        int m;
        cin >> m;
        rep(i, 2) {
            board[i][0] = 0;
            board[i][m + 1] = 0;
            rep(j, 1, m + 1) cin >> board[i][j];
        }
        rep(j, 2, m + 1) {
            board[0][m - j + 1] += board[0][m - j + 2];
            board[1][j] += board[1][j - 1];
        }
        ll minscore = INT64_MAX;
        rep(j, 1, m + 1) {
            ll score = max(board[0][j + 1], board[1][j - 1]);
            minscore = min(minscore, score);
        }
        cout << minscore << '\n';
    }
}
