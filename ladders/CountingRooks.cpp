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

ll N, K;
vector<ll> facts;

ll choose(ll n, ll k, ll M = MOD) {
    return facts[n] * multinv(facts[k] * facts[n - k] % M, M) % M;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> N) {
        cin >> K;
        facts.resize(N + 1), facts[0] = 1;
        rep(i, 1, N + 1) facts[i] = facts[i - 1] * i % MOD;

        ll R = N, C = max(0ll, N - K);
        ll ans = 0;
        rep(k, C + 1) ans = (ans + choose(C, k) * binexp(k, R) % MOD *
                                       ((C + k) % 2 ? MOD - 1 : 1) % MOD) %
                            MOD;
        ans = ans * choose(N, C) % MOD;
        if (R != C) ans = ans * 2 % MOD;

        cout << ans << endl;
    }
}
