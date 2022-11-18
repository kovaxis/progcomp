#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int W, H;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> W >> H;
    double ans[2];

    cout << "? " << 2 * (H + 1) << "\n";
    rep(y, H + 1) {
        int x0 = (y == 0 ? -1 : 0);
        int x1 = (y == H ? -1 : W);
        cout << x0 << " " << y << "\n";
        cout << x1 << " " << y << "\n";
    }
    cout << flush;
    double a;
    cin >> a;
    double x = (1. - a) * W - 0.5;

    cout << "? " << 2 * (W + 1) << "\n";
    rep(x, W + 1) {
        int y0 = (x == 0 ? -1 : 0);
        int y1 = (x == W ? -1 : H);
        cout << x << " " << y0 << "\n";
        cout << x << " " << y1 << "\n";
    }
    cout << flush;
    a;
    cin >> a;
    double y = (1. - a) * H - 0.5;

    cout << "! " << fixed << x << " " << fixed << y << endl;
}

// h(x) = 1 - x / W
// a(x) = (h(x) + h(x+1))/2
// a(x) = (1 - x / W + 1 - x / W - 1 / W) / 2
// a(x) = (2 - 2 * x / W - 1 / W) / 2
// a(x) = 1 - (x + 0.5) / W
// (x + 0.5) / W = 1 - a(x)
// x = (1 - a(x)) * W - 0.5
