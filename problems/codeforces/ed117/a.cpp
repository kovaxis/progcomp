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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        int x, y;
        cin >> x >> y;

        int d = x + y;

        if (d % 2) {
            cout << "-1 -1\n";
            continue;
        }

        d /= 2;
        int x2 = 0, y2 = 0;

        int l = min(d, x);
        x2 += l, d -= l;
        int r = min(d, y);
        y2 += r, d -= r;

        cout << x2 << " " << y2 << "\n";
    }
}
