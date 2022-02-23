#include "../common.h"

#define NOMAIN_UMAP
#include "../ds/umap.cpp"

// take the modulo for possibly negative numbers.
ll mod(ll a, ll M) { return (a % M + M) % M; }

// binary exponentiation modulo M.
ll binexp(ll a, ll m, ll M) {
    assert(m >= 0);
    ll res = 1 % M;
    while (m) {
        if (m & 1) res = (res * a) % M;
        a = (a * a) % M;
        m >>= 1;
    }
    return res;
}

// compute the modular multiplicative inverse, assuming M is prime.
ll multinv(ll a, ll M) { return binexp(a, M - 2, M); }

// calculate gcd(a, b).
// also, calculate x and y such that:
// a * x + b * y == gcd(a, b)
//
// time: O(log min(a, b))
// (ignoring complexity of arithmetic)
ll ext_gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// compute the modular multiplicative inverse, assuming a and MOD are coprime.
// MOD may not be prime.
ll multinv_euc(ll a, ll M) {
    ll x, y;
    ll g = ext_gcd(a, M, x, y);
    assert(g == 1);
    return (x % M + M) % M;
}

// computes euler totative function phi(x), counting the amount of integers in
// [1, x] that are relatively prime to x.
//
// time: O(sqrt(x))
ll eulerphi(ll x) {
    ll phi = 1;
    ll k = 2;
    while (x > 1) {
        if (k * k > x) {
            phi *= x - 1;
            break;
        }
        ll k1 = 1, k0 = 0;
        while (x % k == 0) x /= k, k0 = k1, k1 *= k;
        phi *= k1 - k0;
        k += 1;
    }
    return phi;
}

// N choose K but modular, using a precomputed factorial table.
ll choose(ll* fact, ll n, ll k, ll M) {
    return fact[n] * multinv(fact[k] * fact[n - k] % M, M) % M;
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

// discrete logarithm.
// solve a ^ x = b (mod M) for the smallest x.
// returns -1 if no solution is found.
//
// time: O(sqrt(M))
ll dlog(ll a, ll b, ll M) {
    ll k = 1 % M, s = 0;
    while (true) {
        ll g = __gcd(a, M);
        if (g <= 1) break;
        if (b == k) return s;
        if (b % g != 0) return -1;
        b /= g, M /= g, s += 1, k = a / g * k % M;
    }
    ll N = sqrt(M) + 1;

    static umap<ll, ll> r;
    r.clear();
    ll baq = b;
    rep(q, N + 1) {
        r[baq] = q;
        baq = baq * a % M;
    }

    ll aN = binexp(a, N, M), aNp = k;
    rep(p, 1, N + 1) {
        aNp = aNp * aN % M;
        if (r.count(aNp)) return N * p - r[aNp] + s;
    }
    return -1;
}

#ifndef NOMAIN_MOD

#include "../test.h"

int main() {
    {
        cout << "checking eulerphi... " << flush;
        auto test = [&](int x) {
            int phi = eulerphi(x);
            int phi2 = 0;
            rep(k, 1, x + 1) phi2 += (__gcd(x, k) == 1);
            if (phi != phi2) {
                cerr << "fastphi(" << x << ") = " << phi << " != phi(" << x
                     << ") = " << phi2 << endl;
            }
        };
        rep(x, 1, 5000) test(x);
        rep(i, 1000) test(random_ll(5000, 100000));
        rep(i, 10) test(random_ll(100000, 10000000));
        cout << "all ok" << endl;
    }

    {
        cout << "checking ext_gcd... " << flush;
        auto test = [](ll a, ll b) {
            ll x, y, g;
            g = ext_gcd(a, b, x, y);
            assert(g == __gcd(a, b));
            assert(a * x + b * y == g);
        };
        rep(a, 1000) rep(b, 1000) test(a, b);
        rep(i, 100000)
            test(random_ll(1000, INT32_MAX), random_ll(1000, INT32_MAX));
        cout << "all ok" << endl;
    }

    {
        cout << "checking dlog... " << flush;
        vector<bool> seen;
        auto testyes = [&](ll a, ll x, ll m) {
            // a^x = b mod m
            int b = 1 % m;
            rep(i, x) b = b * a % m;
            seen[b] = true;
            int x2 = dlog(a, b, m);
            auto pr = [&]() {
                cerr << a << "^" << x << " = " << b << " mod " << m;
            };
            if (x2 == -1) {
                cerr << "no solution found for ";
                pr();
                cerr << endl;
            } else if (x2 > x) {
                cerr << "found larger solution " << x2 << " for ";
                pr();
                cerr << endl;
            } else {
                ll b2 = 1 % m;
                rep(i, x2) b2 = b2 * a % m;
                if (b2 != b) {
                    cerr << "found result " << x2 << " for ";
                    pr();
                    cerr << ", but a^x = " << b2 << " instead of " << b << endl;
                }
            }
        };
        auto testmaybe = [&](ll a, ll b, ll m) {
            ll x = dlog(a, b, m);
            if (x == -1) return;
            ll b2 = binexp(a, x, m);
            if (b != b2) {
                cerr << "found result " << x << " for " << a << "^x = " << b
                     << ", but it produces wrong result b = " << b2 << endl;
            }
        };
        rep(m, 80) {
            rep(a, m) {
                seen.assign(m, false);
                rep(x, m) testyes(a, x, m);
                rep(b, m) if (!seen[b]) testmaybe(a, b, m);
            }
        }
        rep(i, 800) {
            ll m = random_ll(1, 1000000001);
            ll a = random_ll(0, m), b = random_ll(0, m);
            testmaybe(a, b, m);
        }
        cout << "all ok" << endl;
    }
}

#endif