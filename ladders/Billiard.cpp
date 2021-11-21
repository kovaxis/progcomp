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

typedef ll T;

struct P {
    T x;
    T y;

    P(T x_, T y_) : x{x_}, y{y_} {}
    P() : x{0}, y{0} {}

    friend ostream& operator<<(ostream& s, const P& self) {
        s << self.x << " " << self.y;
        return s;
    }
    friend istream& operator>>(istream& s, P& self) {
        s >> self.x;
        s >> self.y;
        return s;
    }

    P& operator+=(const P& r) {
        this->x += r.x;
        this->y += r.y;
        return *this;
    }
    friend P operator+(P l, const P& r) { return {l.x + r.x, l.y + r.y}; }

    P& operator-=(const P& r) {
        this->x -= r.x;
        this->y -= r.y;
        return *this;
    }
    friend P operator-(P l, const P& r) { return {l.x - r.x, l.y - r.y}; }
    P operator-() { return {-this->x, -this->y}; }

    P& operator*=(const T& r) {
        this->x *= r;
        this->y *= r;
        return *this;
    }
    friend P operator*(P l, const T& r) { return {l.x * r, l.y * r}; }
    friend P operator*(const T& l, P r) { return {l * r.x, l * r.y}; }

    P& operator/=(const T& r) {
        this->x /= r;
        this->y /= r;
        return *this;
    }
    friend P operator/(P l, const T& r) { return {l.x / r, l.y / r}; }

    // Dot product
    friend T operator*(P l, const P& r) { return l.x * r.x + l.y * r.y; }

    // Cross product
    friend T operator^(P l, const P& r) { return l.x * r.y - r.x * l.y; }

    T magsq() { return this->x * this->x + this->y * this->y; }
    T mag() { return sqrt(this->magsq()); }
    P unit() { return (1. / this->mag()) * (*this); }

    P rotated() { return {-this->y, this->x}; }

    double angle() { return atan2((double)this->y, (double)this->x); }
    float angle_float() { return atan2((float)this->y, (float)this->x); }
    static P from_angle(T angle) { return {(T)cos(angle), (T)sin(angle)}; }
};

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
ll multinv(ll a, ll MOD) {
    ll x, y;
    ll g = ext_gcd(a, MOD, x, y);
    assert(g == 1);
    return (x % MOD + MOD) % MOD;
}

P sz, u0, v0;

ll advance(ll u, ll v, ll w) {
    if (v > 0)
        return w - u;
    else if (v < 0)
        return u;
    else
        return INT64_MAX;
}

bool ispocket(P u) {
    return (u.x == 0 || u.x == sz.x) && (u.y == 0 || u.y == sz.y);
}

ll gettime(ll c) {
    ll n = 2 * sz.y, m = 2 * sz.x;
    c = (c % m + m) % m;
    ll d = __gcd(n, m);
    if (c % d != 0) return INT64_MAX;
    n /= d, c /= d, m /= d;
    return c * multinv(n, m) % m;
}

P getpocketmod(P u1) {
    ll cs[4] = {-u1.x, sz.x - u1.x, -u1.x - sz.y, sz.x - u1.x - sz.y};
    P pocks[4] = {{0, 0}, {sz.x, 0}, {0, sz.y}, {sz.x, sz.y}};
    ll ts[4];
    rep(i, 4) ts[i] = gettime(cs[i]);
    ll mn = INT64_MAX;
    rep(i, 4) mn = min(mn, ts[i]);
    rep(i, 4) if (mn < INT64_MAX && mn == ts[i]) return pocks[i];
    return {-1, -1};
}

P getpocket() {
    ll adv = min(advance(u0.x, v0.x, sz.x), advance(u0.y, v0.y, sz.y));
    P u1 = u0 + v0 * adv;
    if (ispocket(u1)) return u1;
    if (!v0.x || !v0.y) return {-1, -1};

    bool swapped = u1.x == 0 || u1.x == sz.x;
    if (swapped) swap(sz.x, sz.y), swap(u1.x, u1.y), swap(v0.x, v0.y);
    bool invx = v0.x < 0;
    if (invx) u1.x = sz.x - u1.x, v0.x = -v0.x;
    bool invy = u1.y == sz.y;
    if (invy) u1.y = 0, v0.y = -v0.y;

    P pock = getpocketmod(u1);
    if (pock.x == -1) return pock;
    if (invy) pock.y = sz.y - pock.y;
    if (invx) pock.x = sz.x - pock.x;
    if (swapped) swap(pock.x, pock.y);
    return pock;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> sz >> u0 >> v0;

    P pock = getpocket();
    if (pock.x == -1)
        cout << "-1\n";
    else
        cout << pock << "\n";
}
