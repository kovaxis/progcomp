#include "../common.h"

// floor(log2(n)) without precision loss
inline int floor_log2(int n) { return n <= 1 ? 0 : 31 - __builtin_clz(n); }
// ceil(log2(n)) without precision loss
inline int ceil_log2(int n) { return n <= 1 ? 0 : 32 - __builtin_clz(n - 1); }

inline ll floordiv(ll a, ll b) {
    ll d = a / b;
    return d * b == a ? d : d - ((a < 0) ^ (b < 0));
}

inline ll ceildiv(ll a, ll b) {
    ll d = a / b;
    return d * b == a ? d : d - ((a < 0) ^ (b < 0)) + 1;
}

// a^e through binary exponentiation.
ll binexp(ll a, ll e) {
    ll res = 1; // neutral element
    while (e) {
        if (e & 1) res = res * a; // multiplication
        a = a * a;                // multiplication
        e >>= 1;
    }
    return res;
}

#ifndef NOMAIN_ARITH

int main() {
    // Floor division
    assert(floordiv(3, 5) == 0);
    assert(floordiv(7, 5) == 1);
    assert(floordiv(-2, 5) == -1);
    assert(floordiv(-7, 3) == -3);
    assert(floordiv(-6, 3) == -2);
    assert(floordiv(-0, 7) == 0);
    assert(floordiv(2, -5) == -1);
    assert(floordiv(7, -3) == -3);
    assert(floordiv(6, -3) == -2);
    assert(floordiv(0, -7) == 0);

    // Ceil division
    assert(ceildiv(3, 5) == 1);
    assert(ceildiv(7, 5) == 2);
    assert(ceildiv(-2, 5) == 0);
    assert(ceildiv(-7, 3) == -2);
    assert(ceildiv(-6, 3) == -2);
    assert(ceildiv(-0, 7) == 0);
    assert(ceildiv(2, -5) == 0);
    assert(ceildiv(7, -3) == -2);
    assert(ceildiv(6, -3) == -2);
    assert(ceildiv(0, -7) == 0);

    // Count divisors
    assert(count_divisors(1) == 1);
    assert(count_divisors(2) == 2);
    assert(count_divisors(3) == 2);
    assert(count_divisors(4) == 3);
    assert(count_divisors(5) == 2);
    assert(count_divisors(6) == 4);
    assert(count_divisors(7) == 2);
    assert(count_divisors(16) == 5);
    assert(count_divisors(42) == 8);
    assert(count_divisors(101) == 2);
}

#endif
