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

ll P, Q, N, MOD;

ll PtotheNplus1;
ll NtotheQ[1024];

ll choose[1024][1024];

// Binary exponentiation modulo MOD.
ll binexp(ll a, ll m) {
    ll res = 1;
    while (m) {
        if (m & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        m >>= 1;
    }
    return res;
}

ll ext_gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

ll modinv(ll a) {
    ll x, y;
    ll g = ext_gcd(a, MOD, x, y);
    assert(g == 1);
    cerr << a << "^-1 mod " << MOD << " is " << (x % MOD + MOD) % MOD << endl;
    return (x % MOD + MOD) % MOD;
}

// sum k in [1, N] (P^k * k^q)
ll dp[1024];
ll getsum(ll q) {
    if (dp[q] != -1) return dp[q];
    ll ans = PtotheNplus1 * NtotheQ[q] % MOD;
    rep(b, 1, q + 1) ans =
        (ans + MOD + choose[q][b] * getsum(q - b) % MOD * (b % 2 ? -1 : 1)) %
        MOD;
    if (q == 0) ans = PtotheNplus1 - P;
    ans = ans * modinv(P - 1) % MOD;
    cerr << "sum for q = " << q << " is " << ans << endl;
    return dp[q] = ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> P >> Q >> N >> MOD;

    PtotheNplus1 = binexp(P, N + 1);

    {
        ll acc = 1;
        rep(q, 1024) {
            NtotheQ[q] = acc;
            acc = acc * N % MOD;
        }
    }

    rep(i, 1024) rep(j, i + 1) {
        if (j == 0 || j == i) {
            choose[i][j] = 1;
        } else {
            choose[i][j] = (choose[i - 1][j - 1] + choose[i - 1][j]) % MOD;
        }
    }

    rep(q, 1024) dp[q] = -1;

    cout << getsum(Q) << "\n";
}
