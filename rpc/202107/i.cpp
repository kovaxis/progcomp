#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

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
    Vec2 unit() { return (1. / this->mag()) * (*this); }

    Vec2 rotated() { return {-this->y, this->x}; }

    double angle() { return atan2((double)this->y, (double)this->x); }
    float angle_float() { return atan2((float)this->y, (float)this->x); }
    static Vec2 from_angle(T angle) { return {(T)cos(angle), (T)sin(angle)}; }
};

pair<Vec2, Vec2> paths[502];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    rep(i, n) {}
}
