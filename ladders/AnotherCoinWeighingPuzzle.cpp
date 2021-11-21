#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

const ll MOD = 998244353;

// binary exponentiation modulo MOD.
ll binexp(ll a, ll m) {
    ll res = 1;
    while (m) {
        if (m & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        m >>= 1;
    }
    return res;
}

// compute the modular multiplicative inverse, assuming MOD is prime.
ll multinv(ll a) { return binexp(a, MOD - 2); }

ll M, K;

vector<ll> dp;
// count the amount of strings with gcd = x
ll countgcd(ll x) {
    if (dp[x] != -1) return dp[x];
    ll r = (binexp(K / x * 2 + 1, M) - 1 + MOD) % MOD;
    ll k = 2;
    while (k * x <= K) {
        r = (r - countgcd(k * x) + MOD) % MOD;
        k += 1;
    }
    return dp[x] = r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> M >> K;
    dp.assign(K + 1, -1);
    cout << countgcd(1) + 1 << endl;
}
