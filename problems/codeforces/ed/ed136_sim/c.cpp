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
    static const int M = 998244353;

    Mod(ll aa) : a((aa % M + M) % M) {}

    Mod operator+(Mod rhs) const { return (a + rhs.a) % M; }
    Mod operator-(Mod rhs) const { return (a - rhs.a + M) % M; }
    Mod operator-() const { return Mod(0) - *this; }
    Mod operator*(Mod rhs) const { return (ll)a * rhs.a % M; }

    Mod operator+=(Mod rhs) { return *this = *this + rhs; }
    Mod operator-=(Mod rhs) { return *this = *this - rhs; }
    Mod operator*=(Mod rhs) { return *this = *this * rhs; }

    Mod bigmul(ll big) const { return ::bigmul(a, big, M); }

    Mod binexp(ll e) const { return ::binexp(a, e, M); }
    // Mod multinv() const { return ::multinv(a, M); } // prime M
    Mod multinv() const { return ::multinv_euc(a, M); } // possibly composite M
};

Mod fact(int n) {
    Mod f = 1;
    repx(i, 1, n + 1) f *= i;
    return f;
}

Mod choose(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact(n) * (fact(k) * fact(n - k)).multinv();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        int N;
        cin >> N;

        Mod win[2] = {0, 0};
        rep(n, N / 2) {
            bool cur = (N / 2 - 1 - n) % 2;
            win[cur] += choose(2 * n + 1, n + 1);
            win[!cur] += choose(2 * n, n - 1);
        }

        cout << win[0].a << " " << win[1].a << " " << 1 << "\n";
    }
}
