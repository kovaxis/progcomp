#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll MOD = 998244353, ROOT = 15311432;

int binexp(int a, ll e, int M) {
    assert(e >= 0);
    int res = 1 % M;
    while (e) {
        if (e & 1) res = (ll)res * a % M;
        a = (ll)a * a % M;
        e >>= 1;
    }
    return res;
}

int multinv(int a, int M) { return binexp(a, M - 2, M); }

void ntt(vector<int> &a, bool inv) {
    vector<int> wn;
    for (int p = ROOT; p != 1; p = (ll)p * p % MOD) wn.push_back(p);

    int N = a.size(), k = 0, b;
    assert(N == 1 << __builtin_ctz(N) && N <= 1 << wn.size());
    // rep(i, N) a[i] = (a[i] % MOD + MOD) % MOD;

    repx(i, 1, N) {
        for (b = N >> 1; k & b;) k ^= b, b >>= 1;
        if (i < (k ^= b)) swap(a[i], a[k]);
    }

    for (int l = 2; l <= N; l <<= 1) {
        int wl = wn[wn.size() - __builtin_ctz(l)];
        if (inv) wl = multinv(wl, MOD);

        for (int i = 0; i < N; i += l) {
            int w = 1;
            repx(j, 0, l / 2) {
                int u = a[i + j], v = (ll)a[i + j + l / 2] * w % MOD;
                a[i + j] = (u + v) % MOD;
                a[i + j + l / 2] = (u - v + MOD) % MOD;
                w = (ll)w * wl % MOD;
            }
        }
    }

    int q = multinv(N, MOD);
    if (inv) rep(i, N) a[i] = (ll)a[i] * q % MOD;
}

inline int ceil_log2(int n) { return n <= 1 ? 0 : 32 - __builtin_clz(n - 1); }

int K, N;

vector<int> multpoly(vector<int> a, vector<int> b) {
    int n = a.size();
    assert(n == b.size());
    rep(i, n) a[i] = (ll)a[i] * b[i] % MOD;
    return a;
}

vector<int> binexp_poly(vector<int> a, ll e) {
    assert(e >= 0);
    vector<int> res{1};
    res.resize(1 << K);
    ntt(res, false);
    while (e) {
        if (e & 1) res = multpoly(res, a);
        a = multpoly(a, a);
        e >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> K >> N;

    vector<int> a{1, 1};
    a.resize(1 << K);

    ntt(a, false);
    a = binexp_poly(a, N);
    ntt(a, true);

    for (int x : a) cout << x << " ";
    cout << endl;
}
