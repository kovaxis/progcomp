#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

const ll MOD = 998244353, ROOT = 15311432;

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

ll multinv(ll a, ll M) {
    return binexp(a, M - 2, M);
}

// compute the DFT of a power-of-two-length sequence, modulo a special prime
// number with principal root.
//
// the modulus _must_ be a prime number with an Nth root of unity, where N is a
// power of two. the FFT can only be performed on arrays of size <= N.
void ntt(vector<ll> &a, bool inv) {
    vector<ll> wn;
    for (ll p = ROOT; p != 1; p = p * p % MOD) wn.push_back(p);

    int N = a.size(), k = 0, b;
    assert(N == 1 << __builtin_ctz(N) && N <= 1 << wn.size());
    rep(i, N) a[i] = (a[i] % MOD + MOD) % MOD;

    repx(i, 1, N) {
        for (b = N >> 1; k & b;) k ^= b, b >>= 1;
        if (i < (k ^= b)) swap(a[i], a[k]);
    }

    for (int l = 2; l <= N; l <<= 1) {
        ll wl = wn[wn.size() - __builtin_ctz(l)];
        if (inv) wl = multinv(wl, MOD);

        for (int i = 0; i < N; i += l) {
            ll w = 1;
            repx(j, 0, l / 2) {
                ll u = a[i + j], v = a[i + j + l / 2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + l / 2] = (u - v + MOD) % MOD;
                w = w * wl % MOD;
            }
        }
    }

    ll q = multinv(N, MOD);
    if (inv) rep(i, N) a[i] = a[i] * q % MOD;
}

void convolve(vector<ll> &a, vector<ll> b, int n) {
    n = 1 << (32 - __builtin_clz(2 * n - 1));
    a.resize(n), b.resize(n);
    ntt(a, false), ntt(b, false);
    rep(i, n) a[i] = a[i] * b[i] % MOD;
    ntt(a, true);
    a.resize(n);
}

int N, K;

vector<ll> fact;
vector<int> ans;

int truncbase;
vector<ll> truncfactvals;

// calculate n! / truncbase!
ll truncfact(ll n) {
    cerr << "calculating truncfact of " << n << endl;
    assert(n - truncbase >= 0 && n - truncbase < truncfactvals.size());
    return truncfactvals[n - truncbase];
}

vector<int> compute_row_at(ll N, int K) {
    cerr << "computing " << K << " values at row " << N << endl;

    vector<ll> A(K);
    rep(k, K) A[k] = truncfact(N + k) * multinv(fact[k], MOD) % MOD;
    vector<ll> B(K);
    rep(k, min(K, (int)N + 1)) B[k] = multinv(fact[k] * truncfact(N - k) % MOD, MOD);

    cerr << "A:";
    rep(k, K) cerr << " " << A[k];
    cerr << endl;
    cerr << "B:";
    rep(k, K) cerr << " " << B[k];
    cerr << endl;

    convolve(A, B, K);

    vector<int> out(K);
    rep(i, K) out[i] = A[i];

    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    K += 1;

    fact.assign(2 * K + 5, 1);
    repx(n, 1, 2 * K + 5) fact[n] = fact[n - 1] * n % MOD;

    truncbase = max(N - 2 * K, 0);
    truncfactvals.assign(3 * K + 5, 1);
    repx(n, 1, 2 * K + 5) truncfactvals[n] = truncfactvals[n - 1] * (truncbase + n) % MOD;

    ans.resize(K);
    int k = K;
    while (N - k + 1 < 0) {
        ans[--k] = 0;
    }

    vector<int> now = compute_row_at(N - k + 1, k);
    vector<int> old(k);

    while (k > 0) {
        k -= 1;
        ans[k] = now[k];

        swap(now, old);
        now[0] = 1;
        repx(x, 1, k) {
            ll newnow = (ll)now[x - 1] + old[x - 1] + old[x];
            if (newnow >= MOD) newnow -= MOD;
            if (newnow >= MOD) newnow -= MOD;
            now[x] = newnow;
        }
    }

    repx(k, 1, K) {
        cout << ans[k] << " ";
    }
    cout << endl;
}
