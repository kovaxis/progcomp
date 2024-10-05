#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll MOD = 998244353;

ll binexp(ll a, ll e, ll M) {
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

ll M, N;
vector<ll> fact, ifact;

ll comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

ll multicomb(int n, int k) {
    return comb(n + k - 1, k);
}

ll solve() {
    ll ans = comb(M, 2 * N);
    for (int x = 0; 2 * x <= M - 2 * N; x++) {
        ll res = multicomb(N, x) * multicomb(N + 1, M - 2 * N - 2 * x) % MOD;
        ans = (ans + MOD - res) % MOD;
    }
    return 2 * ans % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int fm = 3e6;
    fact.assign(fm, 1);
    repx(i, 1, fm) fact[i] = fact[i - 1] * i % MOD;
    ifact.resize(fm);
    rep(i, fm) ifact[i] = multinv(fact[i]);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> M >> N;
        cout << solve() << "\n";
    }
}
