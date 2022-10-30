#include <bits/stdc++.h>
using namespace std;

typedef double T;

struct Vec2 {
    T x;
    T y;

    Vec2(T x_, T y_) : x{x_}, y{y_} {}
    Vec2() : x{0}, y{0} {}

    friend ostream& operator<<(ostream& out, const Vec2& self) {
        out << "(" << self.x << ", " << self.y << ")";
        return out;
    }
    friend istream& operator>>(istream& in, Vec2& self) {
        in >> self.x;
        in >> self.y;
        return in;
    }

    Vec2& operator+=(const Vec2& r) {
        this->x += r.x;
        this->y += r.y;
        return *this;
    }
    friend Vec2 operator+(Vec2 l, const Vec2& r) {
        return {l.x + r.x, l.y + r.y};
    }

    Vec2& operator-=(const Vec2& r) {
        this->x -= r.x;
        this->y -= r.y;
        return *this;
    }
    friend Vec2 operator-(Vec2 l, const Vec2& r) {
        return {l.x - r.x, l.y - r.y};
    }
    Vec2 operator-() { return {-this->x, -this->y}; }

    Vec2& operator*=(const T& r) {
        this->x *= r;
        this->y *= r;
        return *this;
    }
    friend Vec2 operator*(Vec2 l, const T& r) { return {l.x * r, l.y * r}; }
    friend Vec2 operator*(const T& l, Vec2 r) { return {l * r.x, l * r.y}; }

    Vec2& operator/=(const T& r) {
        this->x /= r;
        this->y /= r;
        return *this;
    }
    friend Vec2 operator/(Vec2 l, const T& r) { return {l.x / r, l.y / r}; }

    // Dot product
    friend T operator*(Vec2 l, const Vec2& r) { return l.x * r.x + l.y * r.y; }

    // Cross product
    friend T operator^(Vec2 l, const Vec2& r) { return l.x * r.y - r.x * l.y; }

    T magsq() { return this->x * this->x + this->y * this->y; }
    T mag() { return sqrt(this->magsq()); }

    double angle() { return atan2((double)this->y, (double)this->x); }
    float angle_float() { return atan2((float)this->y, (float)this->x); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int a_n;
    cin >> a_n;
    vector<Vec2> alice;
    alice.reserve(a_n);
    for (int i = 0; i < a_n; i++) {
        Vec2 p;
        cin >> p;
        alice.push_back(p);
    }
    a_n -= 1;

    int b_n;
    cin >> b_n;
    vector<Vec2> bob;
    bob.reserve(b_n);
    for (int i = 0; i < b_n; i++) {
        Vec2 p;
        cin >> p;
        bob.push_back(p);
    }
    b_n -= 1;

    double a_acc = 0.;
    double b_acc = 0.;
    int a_idx = 0;
    int b_idx = 0;
    double min_dist_sq = INFINITY;
    while (a_idx < a_n && b_idx < b_n) {
        Vec2 a_o = alice[a_idx];
        Vec2 a_d = alice[a_idx + 1] - a_o;
        Vec2 b_o = bob[b_idx];
        Vec2 b_d = bob[b_idx + 1] - b_o;
        double a_start, a_end, b_start, b_end;
        {
            double rem_a = a_d.mag() * (1. - a_acc);
            double rem_b = b_d.mag() * (1. - b_acc);
            a_start = a_acc;
            b_start = b_acc;
            if (rem_a < rem_b) {
                // Advance on A
                a_end = 1.;
                b_acc += rem_a / b_d.mag();
                b_end = b_acc;
                a_acc = 0.;
                a_idx += 1;
            } else {
                // Advance on B
                b_end = 1.;
                a_acc += rem_b / a_d.mag();
                a_end = a_acc;
                b_acc = 0.;
                b_idx += 1;
            }
        }
        a_o += a_d * a_start;
        b_o += b_d * b_start;
        a_d *= a_end - a_start;
        b_d *= b_end - b_start;
        Vec2 o = a_o - b_o;
        Vec2 d = a_d - b_d;
        double s = 0.;
        if (d.magsq() > 0.) {
            s = -(o * d) / d.magsq();
            if (s > 1.) {
                s = 1.;
            } else if (s < 0.) {
                s = 0.;
            }
        }
        min_dist_sq = min(min_dist_sq, (o + d * s).magsq());
    }
    cout << fixed << setw(10) << setprecision(10) << sqrt(min_dist_sq) << endl;
}
