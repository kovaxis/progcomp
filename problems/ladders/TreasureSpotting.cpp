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

bool seg_intersect(P o0, P d0, P o1, P d1) {
    P o = o1 - o0;
    T d = d0 ^ d1;
    if (d == 0) {
        if ((o ^ d0) != 0) return false;
        T e0 = o * d0, e1 = (o + d1) * d0;
        return (0 <= e1 && e0 <= d0 * d0) || (0 <= e0 && e1 <= d0 * d0);
    }
    T n0 = o ^ d0, n1 = o ^ d1;
    if (d < 0) n0 = -n0, n1 = -n1, d = -d;
    return 0 <= n0 && n0 <= d && 0 <= n1 && n1 <= d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int M, N;
    P treasure;
    vector<pair<P, P>> walls;
    vector<pair<P, P>> pirates;

    cin >> M >> N;
    cin >> treasure;
    walls.resize(M);
    rep(i, M) {
        cin >> walls[i].first >> walls[i].second;
        walls[i].second -= walls[i].first;
    }
    pirates.resize(N);
    rep(i, N) {
        cin >> pirates[i].first >> pirates[i].second;
        pirates[i].second -= pirates[i].first;
    }

    for (auto p : pirates) {
        cerr << "pirate " << p.first << ":\n";
        P t = treasure - p.first;
        bool skip = false;
        if (p.second * t < 0 || p.second.magsq() < t.magsq()) {
            cerr << "out of range\n";
            skip = true;
        }
        for (auto p2 : pirates) {
            P d = p2.first - p.first;
            if ((d ^ t) == 0 && d * t > 0 && d.magsq() < t.magsq()) {
                cerr << "collides with pirate " << p2.first << "\n";
                skip = true;
            }
        }
        for (auto w : walls) {
            if (seg_intersect(p.first, t, w.first, w.second)) {
                cerr << "intersects with wall " << w.first << ", " << w.second
                     << "\n";
                skip = true;
            }
        }
        if (skip) {
            cout << "not visible\n";
        } else {
            cout << "visible\n";
        }
    }
}
