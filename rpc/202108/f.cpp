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
bool a[209][209];
bool active[4];
ll total = 0;

void check(bool& active, int x, int y, int lx, int ly) {
    bool wall = !a[lx][ly] && a[x][y];
    total += !active && wall;
    if (!active && wall) {
        // cerr << "wall on (" << x << ", " << y << ") -> (" << lx << ", " << ly
        //    << ")" << endl;
    }
    active = wall;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> H >> W;
    rep(y, H) rep(x, W) {
        char c;
        cin >> c;
        a[x + 1][y + 1] = c == '#';
    }

    rep(i, 1, 208) rep(j, 1, 208) {
        check(active[0], i, j, i - 1, j);
        check(active[1], i, j, i + 1, j);
        check(active[2], j, i, j, i - 1);
        check(active[3], j, i, j, i + 1);
    }
    cout << total << endl;
}
