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

    int tests;
    cin >> tests;
    for (int t = 0; t < tests; t++) {
        Vec2 a, b, c, d;
        cin >> a;
        cin >> b;
        cin >> c;
        cin >> d;
        Vec2 orig = a - c;
        Vec2 delt = (b - a) - (d - c);
        double s = -(orig * delt) / delt.magsq();
        if (delt.magsq() == 0.) {
            s = 0.;
        } else if (s < 0.) {
            s = 0.;
        } else if (s > 1.) {
            s = 1.;
        }
        double mindist = (orig + delt * s).mag();
        cout << "Case " << (t + 1) << ": " << fixed << setw(10)
             << setprecision(10) << mindist << endl;
    }
}
