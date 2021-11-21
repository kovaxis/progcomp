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

const int N = 32;

bool img[2][N][N];
bool imgt[2][4][N][N];

bool getpix(bool im[N][N], int x, int y) {
    if (x >= 0 && x < N && y >= 0 && y < N) {
        return im[x][y];
    } else {
        return false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        rep(l, 2) rep(x, N) rep(y, N) img[l][x][y] = false;
        rep(l, 2) {
            int H, W;
            cin >> H >> W;
            rep(y, H) rep(x, W) {
                char c;
                cin >> c;
                img[l][x][y] = c == '#';
            }
        }

        rep(x, N) rep(y, N) {
            imgt[0][0][x][y] = img[0][x][y];
            imgt[1][0][x][y] = img[0][y][N - x - 1];
        }
        rep(l, 2) rep(x, N) rep(y, N) {
            imgt[l][1][x][y] = imgt[l][0][N - x - 1][y];
            imgt[l][2][x][y] = imgt[l][0][x][N - y - 1];
            imgt[l][3][x][y] = imgt[l][0][N - x - 1][N - y - 1];
        }

        int sim = 0;
        rep(l, 2) rep(k, 4) rep(dx, -32, 32) rep(dy, -32, 32) {
            int score = 0;
            rep(x, N) rep(y, N) {
                score += getpix(imgt[l][k], x + dx, y + dy) == img[1][x][y] &&
                         img[1][x][y];
            }
            sim = max(sim, score);
        }
        cout << sim << '\n';
    }
}
