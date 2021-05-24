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

int h, w;
int row_max[100009];
int tot_max[100009];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (true) {
        cin >> h >> w;
        if (h == 0 || w == 0) {
            break;
        }
        rep(y, h) {
            rep(x, w) {
                int c;
                cin >> c;
                row_max[x] = max(x - 1 < 0 ? 0 : row_max[x - 1],
                                 (x - 2 < 0 ? 0 : row_max[x - 2]) + c);
            }
            tot_max[y] = max(y - 1 < 0 ? 0 : tot_max[y - 1],
                             (y - 2 < 0 ? 0 : tot_max[y - 2]) + row_max[w - 1]);
        }
        cout << tot_max[h - 1] << '\n';
    }
}
