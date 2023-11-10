#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll MOD = 1e9 + 7;

struct Seg {
    ll lo, hi;
    ll g;
};

vector<Seg> segs;

void addseg(ll g, ll lo, ll hi) {
    if (hi < lo) return;
    segs.push_back({lo, hi, g});
}

void calcseg(ll f, ll l, ll r) {
    ll fpow = 1;
    rep(g, 60) {
        ll lo = fpow;
        ll hi = (__int128)fpow * f - 1;
        if ((__int128)fpow * f - 1 > r) hi = r;

        if (hi >= l) {
            addseg(g, max(l, lo), min(r, hi));
        }

        if (hi == r) break;
        fpow *= f;
    }
}

ll intersect(ll lo1, ll hi1, ll lo2, ll hi2) {
    ll lo = max(lo1, lo2);
    ll hi = min(hi1, hi2);
    if (hi < lo) return 0;
    return hi - lo + 1;
}

ll solve(ll L, ll R) {
    ll ans = 0;
    for (Seg seg : segs) {
        ans = (ans + seg.g * intersect(L, R, seg.lo, seg.hi) % MOD) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    repx(f, 2, 60) {
        ll l = 1ll << f;
        ll h = (1ll << (f + 1)) - 1;
        calcseg(f, l, h);
    }

    int Q;
    cin >> Q;
    rep(q, Q) {
        ll l, r;
        cin >> l >> r;
        cout << solve(l, r) << "\n";
    }
}
