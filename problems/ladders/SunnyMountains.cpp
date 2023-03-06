// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=861

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

typedef double T;

struct P {
    T x;
    T y;

    P(T x_, T y_) : x{x_}, y{y_} {}
    P() : x{0}, y{0} {}

    friend ostream &operator<<(ostream &s, const P &self) {
        s << self.x << " " << self.y;
        return s;
    }
    friend istream &operator>>(istream &s, P &self) {
        s >> self.x;
        s >> self.y;
        return s;
    }

    P &operator+=(const P &r) {
        this->x += r.x;
        this->y += r.y;
        return *this;
    }
    friend P operator+(P l, const P &r) { return {l.x + r.x, l.y + r.y}; }

    P &operator-=(const P &r) {
        this->x -= r.x;
        this->y -= r.y;
        return *this;
    }
    friend P operator-(P l, const P &r) { return {l.x - r.x, l.y - r.y}; }
    P operator-() { return {-this->x, -this->y}; }

    P &operator*=(const T &r) {
        this->x *= r;
        this->y *= r;
        return *this;
    }
    friend P operator*(P l, const T &r) { return {l.x * r, l.y * r}; }
    friend P operator*(const T &l, P r) { return {l * r.x, l * r.y}; }

    P &operator/=(const T &r) {
        this->x /= r;
        this->y /= r;
        return *this;
    }
    friend P operator/(P l, const T &r) { return {l.x / r, l.y / r}; }

    // Dot product
    friend T operator*(P l, const P &r) { return l.x * r.x + l.y * r.y; }

    // Cross product (equiv to l.perp() * r in 2D)
    friend T operator^(P l, const P &r) { return l.x * r.y - l.y * r.x; }

    T magsq() { return this->x * this->x + this->y * this->y; }
    T mag() { return sqrt(this->magsq()); }
    P unit() { return (1. / this->mag()) * (*this); }

    P perp() { return {-this->y, this->x}; }

    double angle() { return atan2((double)this->y, (double)this->x); }
    float angle_float() { return atan2((float)this->y, (float)this->x); }
    static P from_angle(T angle) { return {(T)cos(angle), (T)sin(angle)}; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        int N;
        cin >> N;
        vector<P> a(N);
        rep(i, N) cin >> a[i];

        sort(a.begin(), a.end(), [](P a, P b) { return a.x > b.x; });

        double ans = 0., y = 0.;

        repx(i, 1, N) {
            if (a[i].y > y) {
                double dy = a[i].y - y;
                double dx = (a[i].x - a[i - 1].x) / (a[i].y - a[i - 1].y) * dy;
                ans += sqrt(dx * dx + dy * dy);
                y = a[i].y;
            }
        }

        cout << fixed << setw(2) << setprecision(2) << ans << "\n";
    }
}
