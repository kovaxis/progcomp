
#define NOMAIN_BIGINT
#include "bigint.cpp"

// given a set of modular equations, each of the form `x = Ai (mod Pi)`, compute
// `x mod LCM(P0, P1, ..., Pn)`.
// returns a pair of `x` and `LCM(P0, P1, ..., Pn)`.
//
// if the equations cannot be satisfied, {-1, -1} is returned.
pair<bigint, bigint> solve_crt_big(const vector<pair<ll, ll>>& eqs) {
    bigint a0 = eqs[0].first, p0 = eqs[0].second;
    rep(i, 1, eqs.size()) {
        bigint a1 = eqs[i].first, p1 = eqs[i].second;
        bigint k1, k0;
        bigint d = ext_gcd(p1, p0, k1, k0);
        a0 -= a1;
        if (a0.divmod(d) != 0) return {-1, -1};
        p0 /= d, p0 *= p1;
        a0 *= k1, a0 *= p1, a0 += a1;
        a0 %= p0, a0 += p0, a0 %= p0;
    }
    return {a0, p0};
}

ll ext_gcd_small(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = ext_gcd_small(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

pair<ll, ll> solve_crt(const vector<pair<ll, ll>>& eqs) {
    ll a0 = eqs[0].first, p0 = eqs[0].second;
    rep(i, 1, eqs.size()) {
        ll a1 = eqs[i].first, p1 = eqs[i].second;
        ll k1, k0;
        ll d = ext_gcd(p1, p0, k1, k0);
        a0 -= a1;
        if (a0 % d != 0) return {-1, -1};
        p0 = p0 / d * p1;
        a0 = a0 / d * k1 % p0 * p1 % p0 + a1;
        a0 = (a0 % p0 + p0) % p0;
    }
    return {a0, p0};
}

#ifndef NOMAIN_CRT

void crt(const vector<pair<ll, ll>>& eqs, ll res, ll mod) {
    auto sol = solve_crt_big(eqs);
    auto solsmall = solve_crt(eqs);
    cout << "crt equations:" << endl;
    for (auto& eq : eqs) {
        cout << "  x = " << eq.first << " mod " << eq.second << endl;
    }
    cout << "  solution: x = " << sol.first << " mod " << sol.second << endl;

    if (sol != pair<bigint, bigint>{res, mod}) {
        cout << "expected " << res << " mod " << mod << ", got " << sol.first
             << " mod " << sol.second << endl;
    }
    if (sol.second <= INT64_MAX &&
        pair<bigint, bigint>{solsmall.first, solsmall.second} != sol) {
        cout << "mismatch between bigint (" << sol.first << " mod "
             << sol.second << ") and 64-bit (" << solsmall.first << " mod "
             << solsmall.second << ")" << endl;
    }
}

int main() {
    crt(
        {
            {0, 1},
        },
        0, 1);
    crt(
        {
            {1, 2},
            {4, 10},
        },
        -1, -1);
    crt(
        {
            {1, 2},
            {0, 5},
            {0, 7},
        },
        35, 70);
    crt(
        {
            {0, 1},
            {1, 2},
            {0, 5},
            {0, 1},
            {0, 7},
            {0, 1},
        },
        35, 70);
}

#endif
