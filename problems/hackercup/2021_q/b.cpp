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

const int EMPTY = 0;
const int X = 1;
const int O = 2;

int N;
int board[64][64];
bool placed[64][64];
int minmoves;
int winsets;

void check(bool do_swap) {
    rep(i, N) {
        int missing = 0;
        int lastx, lasty;
        rep(j, N) {
            int x = i, y = j;
            if (do_swap) swap(x, y);
            if (board[x][y] == O) missing = -1;
            if (missing != -1) {
                missing += board[x][y] == EMPTY;
                if (board[x][y] == EMPTY) lastx = x, lasty = y;
            }
        }
        if (missing != -1) {
            if (missing < minmoves) {
                minmoves = missing;
                winsets = 0;
            }
            if (missing <= minmoves) {
                winsets += 1;
                if (missing == 1) {
                    winsets -= placed[lastx][lasty];
                    placed[lastx][lasty] = true;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        rep(y, N) rep(x, N) {
            char cell;
            cin >> cell;
            board[x][y] = cell == 'X' ? X : (cell == 'O' ? O : EMPTY);
            placed[x][y] = false;
        }
        minmoves = INT32_MAX;
        winsets = 0;
        rep(s, 2) check(s);
        cout << "Case #" << t + 1 << ": ";
        if (minmoves < INT32_MAX) {
            cout << minmoves << " " << winsets << "\n";
        } else {
            cout << "Impossible\n";
        }
    }
}
