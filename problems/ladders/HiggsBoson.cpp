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

struct frac {
    // denominator must never be negative.
    // if denominator is zero, fraction is infinite.
    ll n, d;

    frac reduced() const {
        ll g = __gcd(abs(n), d);
        return {n / g, d / g};
    }

    int cmp(const frac& rhs) const { return rhs.d * n - d * rhs.n; }
    bool operator<(const frac& r) const { return cmp(r) < 0; }
    bool operator>(const frac& r) const { return cmp(r) > 0; }
    bool operator<=(const frac& r) const { return cmp(r) <= 0; }
    bool operator>=(const frac& r) const { return cmp(r) >= 0; }
    bool operator==(const frac& r) const { return cmp(r) == 0; }
    bool operator!=(const frac& r) const { return cmp(r) != 0; }
};

struct Part {
    ll r1, r0, a1, a0;
} parts[2];

const ll M = 360;

// get the first non-negative instant at which the given particle is at the
// origin (or infinity if it never is).
frac solvezero(Part& p) {
    ll r1 = p.r1, r0 = p.r0;
    if (r1 == 0) {
        if (r0 != 0) return {1, 0};
        return {0, 1};
    }
    if (r1 < 0) r1 = -r1, r0 = -r0;
    if (-r0 < 0) return {1, 0};
    return {-r0, r1};
}

// get the first instant at which the first particle is at the origin, only if
// the second particle is also at the origin at that time.
// otherwise, return infinity.
frac solvezeropair(int i) {
    frac t = solvezero(parts[i]);
    if (t.d == 0) return {1, 0};
    ll r1 = parts[!i].r1, r0 = parts[!i].r0;
    if (r1 * t.n + r0 * t.d == 0) return t;
    return {1, 0};
}

// get the smallest non-negative solution to the following system of equations:
// r1 * t + r0 = 0
// a1 * t = a0 (mod 360)
//
// if it does not exist, returns infinity.
frac solvepair(ll r1, ll r0, ll a1, ll a0) {
    if (r1 == 0) {
        if (r0 != 0) return {1, 0};
        if (a1 == 0) {
            if (a0 % M == 0) return {0, 1};
            return {1, 0};
        }
        if (a1 < 0) a1 = -a1, a0 = -a0;
        a0 = (a0 % M + M) % M;
        return {a0, a1};
    }

    // t = -r0 / r1
    // a1 * (-r0 / r1) = a0 (mod 360) ?
    // a1 * r0 + a0 * r1 = 0 (mod 360 * r1) ?
    if (r1 < 0) r1 = -r1, r0 = -r0;
    if ((a1 * r0 + a0 * r1) % (M * abs(r1)) == 0 && -r0 >= 0) return {-r0, r1};
    return {1, 0};
}

// get the first instant at which both particles are in the same location, or
// infinity if they never meet.
frac getcol() {
    auto &p0 = parts[0], p1 = parts[1];
    frac ans = {1, 0};
    ans = min(ans, solvepair(p0.r1 - p1.r1, p0.r0 - p1.r0, p0.a1 - p1.a1,
                             p1.a0 - p0.a0));
    ans = min(ans, solvepair(p0.r1 + p1.r1, p0.r0 + p1.r0, p0.a1 - p1.a1,
                             p1.a0 - p0.a0 + M / 2));
    ans = min(ans, solvezeropair(0));
    ans = min(ans, solvezeropair(1));
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (true) {
        bool ok = false;
        rep(i, 2) {
            auto& p = parts[i];
            cin >> p.r1 >> p.r0 >> p.a1 >> p.a0;
            ok = ok || p.r1 || p.r0 || p.a1 || p.a0;
        }
        if (!ok) break;

        frac ans = getcol();
        if (ans.d == 0)
            ans = {0, 0};
        else
            ans = ans.reduced();
        cout << ans.n << " " << ans.d << "\n";
    }
}
