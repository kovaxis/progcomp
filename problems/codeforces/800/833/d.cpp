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

ll binexp(ll a, ll e, ll M) {
    assert(e >= 0);
    ll res = 1 % M;
    while (e) {
        if (e & 1) res = res * a;
        a = a * a;
        e >>= 1;
    }
    return res;
}

ll multinv(ll a, ll M) { return binexp(a, M - 2, M); }

// calculate gcd(a, b).
// also, calculate x and y such that:
// a * x + b * y == gcd(a, b)
//
// time: O(log min(a, b))
// (ignoring complexity of arithmetic)
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// compute inverse with any M.
// a and M must be coprime for inverse to exist!
ll multinv_euc(ll a, ll M) {
    ll x, y;
    ext_gcd(a, M, x, y);
    return x;
}

// multiply two big numbers (~10^18) under a large modulo, without resorting to
// bigints.
ll bigmul(ll x, ll y, ll M) {
    ll z = 0;
    while (y) {
        if (y & 1) z = (z + x) % M;
        x = (x << 1) % M, y >>= 1;
    }
    return z;
}

struct Mod {
    int a;
    int M;

    // Mod(ll aa) : a((aa % M + M) % M) {}
    Mod(ll aa, ll m) : M(m), a((aa % m + m) % m) {} // dynamic modulus

    Mod operator+(Mod rhs) const { return Mod((a + rhs.a) % M, M); }
    Mod operator-(Mod rhs) const { return Mod((a - rhs.a + M) % M, M); }
    Mod operator-() const { return Mod(0, M) - *this; }
    Mod operator*(Mod rhs) const { return Mod((ll)a * rhs.a % M, M); }

    Mod operator+=(Mod rhs) { *this = *this + rhs; }
    Mod operator-=(Mod rhs) { *this = *this - rhs; }
    Mod operator*=(Mod rhs) { *this = *this * rhs; }

    Mod bigmul(ll big) const { return Mod(::bigmul(a, big, M), M); }

    Mod binexp(ll e) const { return Mod(::binexp(a, e, M), M); }
    // Mod multinv() const { return Mod(::multinv(a, M), M); } // prime M
    Mod multinv() const { return Mod(::multinv_euc(a, M), M); } // possibly composite M
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        int A, B, D;
        cin >> A >> B >> D;

        int lobits = 0;
        while (D % 2 == 0) lobits += 1, D >>= 1;
        cerr << "D = " << D << ", lobits = " << lobits << endl;

        if ((A & ((1 << lobits) - 1)) || (B & ((1 << lobits) - 1))) {
            cout << "-1\n";
            continue;
        }

        A >>= lobits, B >>= lobits;
        int nbits = 30 - lobits;

        cerr << "A = " << A << ", B = " << B << ", nbits = " << nbits << endl;

        int ab = A | B;
        Mod mult = -Mod(1 << nbits, D);
        if (__gcd(mult.a, D) != 1) {
            cout << "-1\n";
            continue;
        }
        Mod xh = mult.multinv() * Mod(ab, D);

        ll ans = ((((ll)xh.a) << nbits) | ab) << lobits;
        cout << ans << "\n";
    }
}
