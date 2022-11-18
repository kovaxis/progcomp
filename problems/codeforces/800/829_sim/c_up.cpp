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

int N;
vector<int> A;

int solve() {
    int Z = 0, U = 0;
    rep(i, N)(A[i] ? U : Z) += 1;
    int K = min(Z, U);
    int M = (ll)N * (N - 1) / 2 % MOD;

    int fk = 0;
    if (Z < U) {
        // count zeros in first segment
        rep(i, Z) fk += 1 - A[i];
    } else {
        // count ones in second segment
        repx(i, Z, N) fk += A[i];
    }

    int e = 0;
    invrepx(k, fk, K) {
        e = add(e, mul(M, multinv(binexp(K - k, 2))));
    }

    return e;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        A.resize(N);
        rep(i, N) cin >> A[i];

        cout << solve() << "\n";
    }
}
