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

ll binexp(ll a, ll m) {
    ll res = 1;
    while (m) {
        if (m & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        m >>= 1;
    }
    return res;
}

ll fact[200001];
map<int, ll> counts;

// Compute the modular multiplicative inverse, assuming MOD is prime.
ll multinv(ll a) { return binexp(a, MOD - 2); }

// N choose K but modular, using a precomputed factorial table.
ll choose(ll n, ll k) {
    return fact[n] * multinv(fact[k] * fact[n - k] % MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    fact[0] = 1;
    rep(i, 1, 200001) fact[i] = fact[i - 1] * (ll)i % MOD;

    int T;
    cin >> T;
    rep(t, T) {
        ll N;
        cin >> N;
        int mx[2] = {0, 0};
        counts.clear();
        rep(i, N) {
            int a;
            cin >> a;
            if (a >= mx[0])
                mx[1] = mx[0], mx[0] = a;
            else if (a >= mx[1])
                mx[1] = a;
            counts[a] += 1;
        }
        int diff = mx[0] - mx[1];
        if (diff >= 2) {
            cout << "0\n";
        } else if (diff == 1) {
            ll ans = fact[N];
            ll mnc = counts[mx[1]];
            rep(i, mnc, N) {
                ans -=
                    choose(i, mnc) * fact[mnc] % MOD * fact[N - mnc - 1] % MOD;
                ans = (ans + MOD) % MOD;
            }
            cout << ans << "\n";
        } else if (diff == 0) {
            cout << fact[N] << "\n";
        }
    }
}
