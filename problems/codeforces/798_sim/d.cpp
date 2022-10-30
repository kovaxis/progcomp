#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int INF = 1e8;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        int N, M;
        cin >> N >> M;
        int l = INF, r = -INF, u = INF, d = -INF;
        rep(y, N) rep(x, M) {
            char c;
            cin >> c;
            int x2 = x - y, y2 = x + y;
            if (c == 'B') {
                l = min(l, x2);
                r = max(r, x2);
                u = min(u, y2);
                d = max(d, y2);
            }
        }

        int mdist = INF, tx, ty;
        rep(y, N) rep(x, M) {
            int x2 = x - y, y2 = x + y;
            int dist = max(max(x2 - l, r - x2), max(y2 - u, d - y2));
            if (dist < mdist) mdist = dist, tx = x, ty = y;
        }

        cout << ty + 1 << " " << tx + 1 << "\n";
    }
}
