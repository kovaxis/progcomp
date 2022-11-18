#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int MOD = 998244353;

int add(int a, int b) { return (a + b) % MOD; }
int sub(int a, int b) { return (a - b + MOD) % MOD; }
int mul(int a, int b) { return (ll)a * b % MOD; }

// binary exponentiation modulo M.
int binexp(int a, int m) {
    assert(m >= 0);
    int res = 1 % MOD;
    while (m) {
        if (m & 1) res = mul(res, a);
        a = mul(a, a);
        m >>= 1;
    }
    return res;
}

// compute the modular multiplicative inverse, assuming M is prime.
int multinv(int a) { return binexp(a, MOD - 2); }

int N, Z, U;

int solve() {
    int K = min(Z, U);
    vector<int> a(K), b(K), c(K), d(K);
    rep(k, K) {
        a[k] = mul(k, k);
        c[k] = mul(Z - k, U - k);
        d[k] = add(a[k], c[k]);
        b[k] = sub((ll)N * (N - 1) / 2 % MOD, d[k]);
        cerr << a[k] << " * E[" << k - 1 << "] + " << b[k] << " * E[" << k << "] + " << c[k] << " * E[" << k + 1 << "] = " << d[k] << endl;
    }

    rep(k, K - 1) {
        // row[k+1] += -a[k+1] / b[k] * row[k]
        int mult = sub(0, mul(a[k + 1], multinv(b[k])));
        a[k + 1] = add(a[k + 1], mul(b[k], mult)); // a[k+1] = 0
        b[k + 1] = add(b[k + 1], mul(c[k], mult));
        d[k + 1] = add(d[k + 1], mul(d[k], mult));
    }

    int e_kp1 = 0; // e[K] = 0
    invrep(k, K) {
        // after cancelling `a`:
        // b[k] * e[k] + c[k] * e[k+1] = d[k]
        int e = mul(sub(d[k], mul(c[k], e_kp1)), multinv(b[k]));
        cerr << "E[" << k << "] = " << e << endl;
        e_kp1 = e;
    }

    return e_kp1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        Z = 0, U = 0;
        rep(i, N) {
            int x;
            cin >> x;
            if (x == 0) Z += 1;
            if (x == 1) U += 1;
        }

        cout << solve() << "\n";
    }
}
