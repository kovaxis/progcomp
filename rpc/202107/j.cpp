#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int sudoku[9][9];

void can_place_at(int x, int y, bool *out) {
    if (sudoku[x][y] != 0) {
        rep(i, 9) out[i] = false;
        return;
    }
    rep(i, 9) out[i] = true;
    int bx = x / 3 * 3, by = y / 3 * 3;
    rep(sx, 3) rep(sy, 3) {
        if (sudoku[bx + sx][by + sy] != 0)
            out[sudoku[bx + sx][by + sy] - 1] = false;
    }
    rep(sub, 9) {
        if (sudoku[x][sub] != 0) out[sudoku[x][sub] - 1] = false;
        if (sudoku[sub][y] != 0) out[sudoku[sub][y] - 1] = false;
    }
}

bool svr() {
    bool adv = false;
    rep(x, 9) rep(y, 9) {
        if (sudoku[x][y] != 0) continue;
        bool avail[9];
        can_place_at(x, y, avail);
        int num = 0;
        rep(i, 9) {
            if (avail[i]) {
                if (num == 0)
                    num = i + 1;
                else
                    num = -1;
            }
        }
        if (num > 0) {
            sudoku[x][y] = num;
            adv = true;
        }
    }
    return adv;
}

bool ulr() {
    bool adv = false;
    rep(s0, 9) {
        bool row[9][9];
        bool col[9][9];
        bool sub[9][9];
        rep(i, 9) {
            can_place_at(i, s0, row[i]);
            can_place_at(s0, i, col[i]);
        }
        int bx = s0 % 3 * 3;
        int by = s0 / 3 * 3;
        rep(sy, 3) rep(sx, 3) {
            can_place_at(bx + sx, by + sy, sub[sx + sy * 3]);
        }
        rep(num, 9) {
            int rowpos = -1;
            int colpos = -1;
            int subpos = -1;
            rep(i, 9) {
                if (row[i][num]) {
                    if (rowpos == -1)
                        rowpos = i;
                    else
                        rowpos = -2;
                }
                if (col[i][num]) {
                    if (colpos == -1)
                        colpos = i;
                    else
                        colpos = -2;
                }
                if (sub[i][num]) {
                    if (subpos == -1)
                        subpos = i;
                    else
                        subpos = -2;
                }
            }
            if (rowpos >= 0) {
                sudoku[rowpos][s0] = num + 1;
                adv = true;
            }
            if (colpos >= 0) {
                sudoku[s0][colpos] = num + 1;
                adv = true;
            }
            if (subpos >= 0) {
                sudoku[bx + subpos % 3][by + subpos / 3] = num + 1;
                adv = true;
            }
        }
    }
    return adv;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    rep(y, 9) {
        rep(x, 9) { cin >> sudoku[x][y]; }
    }

    while (true) {
        if (!svr() && !ulr()) break;
    }
    bool ready = true;
    rep(x, 9) rep(y, 9) if (sudoku[x][y] == 0) ready = false;
    if (ready) {
        cout << "Easy\n";
    } else {
        cout << "Not easy\n";
    }
    rep(y, 9) {
        rep(x, 9) {
            if (sudoku[x][y] == 0)
                cout << ".";
            else
                cout << sudoku[x][y];
            cout << " \n"[x == 8];
        }
    }
}
