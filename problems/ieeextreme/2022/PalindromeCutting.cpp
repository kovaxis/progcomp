#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define DBG 0

#define cerr \
    if (DBG) cerr

// MOD = 2^23 * 119 + 1
const int MOD = 998244353, ROOT = 104191056, ROOTPOW = 1 << 23;

int add(int a, int b, int M = MOD) {
    return (a + b) % M;
}

int sub(int a, int b, int M = MOD) {
    return (a - b + M) % M;
}

int mul(int a, int b, int M = MOD) {
    return (ll)a * b % M;
}

// binary exponentiation modulo M.
int binexp(int a, int m, int M = MOD) {
    assert(m >= 0);
    int res = 1 % M;
    while (m) {
        if (m & 1) res = mul(res, a);
        a = mul(a, a);
        m >>= 1;
    }
    return res;
}

// compute the modular multiplicative inverse, assuming M is prime.
int multinv(int a, int M = MOD) { return binexp(a, M - 2, M); }

void fft(vector<int> &a, bool inv) {
    int N = a.size(), k = 0;
    assert(N == 1 << __builtin_ctz(N) && N <= ROOTPOW);

    repx(i, 1, N) {
        int b = N >> 1;
        while (k & b) k ^= b, b >>= 1;
        k ^= b;
        if (i < k) swap(a[i], a[k]);
    }

    for (int l = 2; l <= N; l <<= 1) {
        int wl = inv ? multinv(ROOT, MOD) : ROOT;
        for (int i = ROOTPOW; i > l; i >>= 1) wl = mul(wl, wl);
        for (int i = 0; i < N; i += l) {
            int w = 1;
            repx(j, 0, l / 2) {
                int u = a[i + j], v = mul(a[i + j + l / 2], w);
                a[i + j] = add(u, v);
                a[i + j + l / 2] = sub(u, v);
                w = mul(w, wl);
            }
        }
    }

    int ninv = multinv(N, MOD);
    if (inv)
        for (int &x : a) x = mul(x, ninv);
}

void convolve(vector<int> &a, const vector<int> &bb, int n) {
    static vector<int> b;

    a.resize(n), b.assign(bb.begin(), bb.begin() + n);
    int nn = 1 << (32 - __builtin_clz(2 * n - 1));
    a.resize(nn), b.resize(nn);
    fft(a, false), fft(b, false);
    rep(i, nn) a[i] = mul(a[i], b[i]);
    fft(a, true);
    a.resize(n);
}

int N, M;
vector<int> dp, b;

void solve(int l, int r) {
    if (r - l == 1) cerr << "dp[" << l << "] = " << dp[l] << endl;
    if (r - l <= 1) return;
    int m = (l + r) / 2;
    solve(l, m);
    vector<int> sub(dp.begin() + l, dp.begin() + m);
    sub.resize(r - l);

    cerr << "convolving";
    for (ll x : sub) cerr << " " << x;
    cerr << " *";
    rep(i, sub.size()) cerr << " " << b[i];
    cerr << endl;

    convolve(sub, b, sub.size());

    cerr << "  result:";
    for (ll x : sub) cerr << " " << x;
    cerr << endl;

    repx(i, m, r) dp[i] = add(dp[i], sub[i - l]);
    return solve(m, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    N /= 2;
    dp.resize(N + 1);

    b.resize(N + 1);
    b[1] = M;
    b[2] = mul(M, sub(M, 1));
    repx(i, 3, N + 1) b[i] = i % 2 == 0 ? sub(mul(mul(M, M), b[i - 2]), b[i / 2]) : mul(M, b[i - 1]);

    cerr << "b:";
    for (ll x : b) cerr << " " << x;
    cerr << endl;

    dp[0] = 1;
    solve(0, N + 1);

    cout << dp[N] << endl;
}
