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

    friend ostream& operator<<(ostream& out, const P& self) {
        out << "(" << self.x << ", " << self.y << ")";
        return out;
    }
    friend istream& operator>>(istream& in, P& self) {
        in >> self.x;
        in >> self.y;
        return in;
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

const ll RANGE = 1000009;
const ll INF = INT32_MAX;

// x, min/max
// y
ll inters_raw[2 * RANGE + 1][2];
ll* inters = inters_raw + RANGE;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vec<P> points;
    points.resize(N);
    rep(i, N) cin >> points[i];

    rep(x, -RANGE, RANGE) inters[x] = {INF, -INF};
    rep(i, N) {
        P o = points[i];
        P d = points[(i + 1) % N] - points[i];
        rep(dx, abs(d.x)) { ll y = }
    }
}
