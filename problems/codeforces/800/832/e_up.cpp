#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll MOD = 1e9 + 7;

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

vector<ll> fact;

ll choose(ll n, ll k) {
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int fn = 5e6 + 9;
    fact.resize(fn + 1);
    rep(i, fn) fact[i + 1] = fact[i] *

                             int TC;
    cin >> TC;
    while (TC--) {
    }
}
