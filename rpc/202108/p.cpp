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

// 0 = none
// 1 = bird
// 2 = seen
int birds[1001][1001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w, N;
    cin >> h >> w >> N;
    rep(y, h) rep(x, w) cin >> birds[x][y];
    int total = 0;
    rep(i, N) {
        int by, bx;
        cin >> by >> bx;
        rep(ox, -1, 2) rep(oy, -1, 2) {
            int x = bx - 1 + ox, y = by - 1 + oy;
            if (x < 0 || x >= w || y < 0 || y >= h) continue;
            if (birds[x][y] != 2) {
                total += birds[x][y];
                birds[x][y] = 2;
            }
        }
    }
    cout << total << endl;
}
