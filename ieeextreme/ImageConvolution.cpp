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

int imgsize[2][2];
int img[2][512][512];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        rep(l, 2) {
            cin >> imgsize[l][1] >> imgsize[l][0];
            rep(y, imgsize[l][1]) rep(x, imgsize[l][0]) {
                char c;
                cin >> c;
                if (c == '.')
                    img[l][x][y] = -1;
                else if (c == '#')
                    img[l][x][y] = 1;
                else
                    img[l][x][y] = 0;
            }
        }

        int matches = 0;
        rep(dx, imgsize[0][0] - imgsize[1][0] + 1)
            rep(dy, imgsize[0][1] - imgsize[1][1] + 1) {
            bool match = true;
            rep(x, imgsize[1][0]) rep(y, imgsize[1][1]) {
                if (img[0][x + dx][y + dy] * img[1][x][y] < 0) match = false;
            }
            matches += match;
        }

        cout << matches << '\n';
    }
}
