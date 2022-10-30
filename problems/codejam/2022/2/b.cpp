#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (ll i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (ll i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

ll R;

bool isbad(ll x, ll y) {
    ll d = max(x, y);
    ll l = 0, r = R;
    while (l != r) {
        ll m = (l + r) / 2;
        if (m * m <= x * x + y * y - d) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return x * x + y * y - d < l * l && l * l <= x * x + y * y + d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        cout << "Case #" << tc + 1 << ": ";

        cin >> R;

        vector<ll> squares;
        rep(r, R + 1) squares.push_back(r * r);

        ll cnt = 0;
        repx(x, 1, R + 1) repx(y, 1, R + 1) {
            bool good = x * x + y * y <= R * (R + 1);

            bool bad = isbad(x, y);

            cnt += good != bad;
        }

        cout << cnt * 4 << "\n";
    }
}
