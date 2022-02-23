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

int W, H;
vector<vector<char>> cells;

bool canlab(int x, int y) { return cells[x][y] == 'L' || cells[x][y] == '+'; }

void explore(int x, int y) {
    if (cells[x][y] != '.') return;
    int empty = 0;
    empty += cells[x + 1][y] == '.';
    empty += cells[x - 1][y] == '.';
    empty += cells[x][y + 1] == '.';
    empty += cells[x][y - 1] == '.';
    if (empty <= 1) {
        cells[x][y] = '+';
        explore(x + 1, y);
        explore(x - 1, y);
        explore(x, y + 1);
        explore(x, y - 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> H >> W;
        cells.assign(W + 2, vector<char>(H + 2, '#'));
        rep(y, 1, H + 1) rep(x, 1, W + 1) cin >> cells[x][y];

        int lx, ly;
        rep(x, 1, W + 1) rep(y, 1, H + 1) if (cells[x][y] == 'L') lx = x,
                                                                  ly = y;
        explore(lx - 1, ly);
        explore(lx + 1, ly);
        explore(lx, ly - 1);
        explore(lx, ly + 1);
        rep(y, 1, H + 1) {
            rep(x, 1, W + 1) cout << cells[x][y];
            cout << "\n";
        }
    }
}
