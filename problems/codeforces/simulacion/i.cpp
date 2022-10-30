#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

typedef long long ll;

int n;
int time[3][400];

bool try_comb(int start, int a, int b, int c) {
    int ax = 0, bx = 0;
    int moveidx = 0;
    int movedist = 0;
    rep(iraw, n) {
        int i = (start + iraw) % n;
        bx += time[b][i];
        int diff = bx - ax - movedist;
        while (diff > 0) {
            int mv = time[b][(start + moveidx) % n];
            diff -= mv;
            movedist += mv;
            moveidx += 1;
        }
        ax += time[a][i];
    }
    if (moveidx >= n) return false;

    int bstart = (start + moveidx) % n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    rep(i, n) {
        int t;
        cin >> t;
        rep(j, 3) { time[j][i] = t; }
    }
    rep(i, n) {
        rep(a, 3) {
            rep(b, a + 1, 3) {
                rep(c, b + 1, 3) {
                    if (try_comb(i, a, b, c)) {
                        return 0;
                    }
                }
            }
        }
    }
    cout << "impossible\n";
}
