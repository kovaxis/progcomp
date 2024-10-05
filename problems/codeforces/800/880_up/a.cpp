#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

ll A, B, C, K;
ll ans_a, ans_b, ans_c;

pair<ll, ll> mm(int d) {
    ll m = 1;
    rep(i, d - 1) m *= 10;
    ll M = 1;
    rep(i, d) M *= 10;
    return {m, M};
}

bool solve() {
    auto [amin, amax] = mm(A);
    auto [cmin, cmax] = mm(C);
    ll k = K - 1;
    repx(a, amin, amax) {
        auto [bmin, bmax] = mm(B);
        bmin = max(bmin, cmin - a);
        bmax = min(bmax, cmax - a);
        if (bmin < bmax) {
            ll cnt = bmax - bmin;
            if (k < cnt) {
                ll b = bmin + k;
                ans_a = a;
                ans_b = b;
                ans_c = a + b;
                return true;
            } else {
                k -= cnt;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> A >> B >> C >> K;
        if (solve()) {
            cout << ans_a << " + " << ans_b << " = " << ans_c << "\n";
        } else {
            cout << "-1\n";
        }
    }
}
