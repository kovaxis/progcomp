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

const int DX[8] = {1, 1, 0, -1, -1, -1, 0, 1};
const int DY[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int w, h;
string word;
char letters[12][12];

bool possible(int x, int y, int wpos, int k, int dir);

bool possible_nc(int x, int y, int wpos, int k, int dir) {
    if (letters[x][y] != word[wpos]) return false;
    if (wpos == word.size() - 1) return k == 0;
    bool p = false;
    rep(d, 8) {
        int consk = dir != 8 && d != dir;
        p = p || possible(x + DX[d], y + DY[d], wpos + 1, k - consk, d);
    }
    /*if (p) {
        cout << "(" << x << ", " << y << ") pos[" << wpos << "]=" << word[wpos]
             << " k=" << k << " dir=" << dir << " is possible" << endl;
    }*/
    return p;
}

// x, y, wordpos, kinks, dir
// possible
uint8_t dp[12][12][101][101][9];

bool possible(int x, int y, int wpos, int k, int dir) {
    if (k < 0) return false;
    uint8_t& cache = dp[x][y][wpos][k][dir];
    if (cache != 0) return cache - 1;
    bool p = possible_nc(x, y, wpos, k, dir);
    cache = ((uint8_t)p) + 1;
    return p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> h >> w;
    rep(y, h) {
        rep(x, w) { cin >> letters[x + 1][y + 1]; }
    }
    ll kinks;
    cin >> kinks;
    cin >> word;
    if (kinks >= word.size()) {
        cout << "No\n";
        return 0;
    }
    bool p = false;
    rep(y, h) rep(x, w) p = p || possible(x + 1, y + 1, 0, kinks, 8);
    if (p) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}
