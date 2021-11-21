#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

const ll MOD = 1000000007;

ll fact[200001];

ll binexp(ll a, ll m) {
    ll res = 1;
    while (m) {
        if (m & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return res;
}

ll inv(ll a) { return binexp(a, MOD - 2); }

ll choose(ll n, ll k) {
    return fact[n] * inv(fact[k] * fact[n - k] % MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    {
        ll acc = 1;
        ll i = 0;
        while (i < 200001) {
            fact[i++] = acc;
            acc = (acc * i) % MOD;
        }
    }

    int T;
    cin >> T;
    rep(t, T) {
        ll n, l, r;
        cin >> n >> l >> r;
        l = 1 - l;
        r -= n;
        ll upcount = n / 2;
        cerr << "l = " << l << ", r = " << r << endl;
        ll ans = min(l, r) * choose(n, upcount) % MOD;
        cerr << ans << " fully free arrays" << endl;
        ll i = min(l, r);
        while (true) {
            i += 1;
            ll forcep = max(i - l, 0ll);
            ll forcen = max(i - r, 0ll);
            ll free = n - forcep - forcen;
            if (free < 0) break;

            cerr << ex2[n - force] << " " << force
                 << "-restricted arrays of size " << i << endl;
            ans = (ans + ex2[n - force]) % MOD;
        }
        cout << ans << '\n';
    }
}
