// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3060

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cout << fixed << setw(3) << setprecision(3);

    while (true) {
        double l, w, h, a;
        if (!(cin >> l >> w >> h >> a)) break;
        double v1 = l * (h - tan(a / 180 * M_PI) * l / 2);
        double v2 = h * h * tan((90 - a) / 180 * M_PI) / 2;
        cout << w * (v1 > l * h / 2 ? v1 : v2) << " mL\n";
    }
}
