// TODO: test upsolve

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

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

ll multinv(ll a, ll M) { return binexp(a, M - 2, M); }

const int MOD = 998244353;
const int FMAX = 2e6;

int N, K;
vector<int> fact, invfact;

int comb(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    return (ll)fact[n] * invfact[k] % MOD * invfact[n - k] % MOD;
}

int solve() {
    int ans = 1;
    for (int M = 2 * K; M <= N; M += 2 * K) {
        // cerr << "comb(" << N << ", " << cnt << ") = " << comb(N, cnt) << endl;
        int C = M - 2 * (K - 1);
        ans = ((ll)ans + comb(N, M) - comb(N - C + 1, M - C + 1) + MOD) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    fact.resize(FMAX);
    fact[0] = 1;
    repx(i, 1, FMAX) fact[i] = (ll)fact[i - 1] * i % MOD;
    invfact.resize(FMAX);
    rep(i, FMAX) invfact[i] = multinv(fact[i], MOD);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        repx(k, 1, (N - 1) / 2 + 1) {
            K = k;
            cout << solve() << " ";
        }
        // cout << "\n";
        cout << endl; // TODO: REPLACE
    }
}
