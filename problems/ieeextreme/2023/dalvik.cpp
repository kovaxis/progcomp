#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

ll v0, v1, v2;

ll round_div(ll num, ll div) {
    return (num + div / 2) / div;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        cin >> v0 >> v1 >> v2;
        ll best_num = 100000;
        ll best_div = 1;
        ll best_x = -1;
        ll best_k = -1;
        repx(x, 1, v2 + 1) {
            // k * v1 / x approx v0
            // k = round(v0 / (v1 / x))
            // k = round(v0 * x / v1)
            ll k = round_div(v0 * x, v1);
            // v0 - k * v1 / x
            // (v0 * x - k * v1) / x
            ll dnum = abs(v0 * x - k * v1);
            ll ddiv = x;
            ll g = __gcd(dnum, ddiv);
            dnum /= g, ddiv /= g;
            // dnum/ddiv < best_num/best_div
            if (dnum * best_div < best_num * ddiv) {
                best_num = dnum;
                best_div = ddiv;
                best_x = x;
                best_k = k;
            }
        }
        // cerr << "d = " << best_num << "/" << best_div << endl;
        // cerr << "x = " << best_x << endl;
        // cerr << "k = " << best_k << endl;
        cout << best_x << "\n";
    }
}
