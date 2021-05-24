
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

bool solve(int sudoku[6][6][2], int x, int y) {
    int forbidden = 0;
    rep(i, 6) {
        if (sudoku[x][i][0] > 0) {
            forbidden |= 1 << (sudoku[x][i][0] - 1);
        }
        if (sudoku[x][i][1] > 0) {
            forbidden |= 1 << (sudoku[x][i][1] - 1);
        }
        if (sudoku[i][y][0] > 0) {
            forbidden |= 1 << (sudoku[i][y][0] - 1);
        }
        if (sudoku[i][y][1] > 0) {
            forbidden |= 1 << (sudoku[i][y][1] - 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int sudoku[6][6][2];
    rep(y, 6) {
        rep(x, 6) {
            char lc, rc;
            cin >> lc >> rc;
            int l;
            if (lc == '-') {
                l = 0;
            } else {
                l = lc - '0';
            }
            if (rc == '/') {
                cin >> rc;
                if (rc == '-') {
                    r = 0;
                } else {
                    r = rc - '0';
                }
            } else {
                r = -1;
            }
            sudoku[x][y] = {l, r};
        }
    }

    solve(sudoku, 0, 0);
}
