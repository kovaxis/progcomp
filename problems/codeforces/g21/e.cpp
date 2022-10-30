#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll MOD = 1e9 + 7;

vector<ll> fact;

// binary exponentiation modulo M.
ll binexp(ll a, ll m, ll M = MOD) {
    assert(m >= 0);
    ll res = 1 % M;
    while (m) {
        if (m & 1) res = (res * a) % M;
        a = (a * a) % M;
        m >>= 1;
    }
    return res;
}

// compute the modular multiplicative inverse, assuming M is prime.
ll multinv(ll a, ll M = MOD) { return binexp(a, M - 2, M); }

// N choose K but modular, using a precomputed factorial table.
ll choose(ll n, ll k, ll M = MOD) {
    return fact[n] * multinv(fact[k] * fact[n - k] % M, M) % M;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    fact.resize(5e5 + 1);
    fact[0] = 1;
    rep(i, 5e5) fact[i + 1] = fact[i] * (i + 1) % MOD;

    ll N;
    cin >> N;
    N += 1;
    vector<ll> a(N);
    rep(i, N) cin >> a[i];

    ll ans = 0;
    rep(i, N) {
        if (a[i] == 0) break;
        ll x = choose(i + 1 + a[i] - 1, a[i] - 1);
        // cerr << "row " << i << " has " << x << " clicks" << endl;
        ans = (ans + x) % MOD;
    }

    cout << ans << endl;
}
