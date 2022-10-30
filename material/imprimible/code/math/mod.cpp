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
    repx(p, 1, N + 1) {
        aNp = aNp * aN % M;
        if (r.count(aNp)) return N * p - r[aNp] + s;
    }
    return -1;
}