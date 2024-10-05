#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll MOD = 999999893;

ll binexp(ll a, ll e, ll M = MOD) {
    assert(e >= 0);
    ll res = 1 % M;
    while (e) {
        if (e & 1) res = res * a % M;
        a = a * a % M;
        e >>= 1;
    }
    return res;
}

ll multinv(ll a, ll M = MOD) { return binexp(a, M - 2, M); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        ll N;
        cin >> N;

        ll a = N / 2;
        ll b = (N - 1) / 2;

        ll x = (binexp(2, a) - 1 + MOD) * 2 % MOD;
        ll y = (binexp(2, b) - 1 + MOD) * 2 % MOD;
        ll z = (y + 2) % MOD;

        ll ans = (y - z + MOD) % MOD * x % MOD * multinv((x * x % MOD - 2 * z % MOD * z % MOD + MOD) % MOD) % MOD;
        cout << ans << "\n";
    }
}
