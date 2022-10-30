#include <bits/stdc++.h>
using namespace std;

typedef int T;

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

Vec2 rotate(Vec2 in) { return {in.x - in.y, in.x + in.y}; }
Vec2 unrotate(Vec2 out) { return {(out.x + out.y) / 2, (out.y - out.x) / 2}; }

bool is_in_rect(Vec2 p0, Vec2 p1, Vec2 p) {
    return p.x >= p0.x && p.x <= p1.x && p.y >= p0.y && p.y <= p1.y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    Vec2 s0 = {9999, 9999};
    Vec2 s1 = {-9999, -9999};
    Vec2 sps[5];
    for (int i = 0; i < 4; i++) {
        Vec2 p;
        cin >> p;
        sps[i] = rotate(p);
        s0.x = min(s0.x, p.x);
        s0.y = min(s0.y, p.y);
        s1.x = max(s1.x, p.x);
        s1.y = max(s1.y, p.y);
    }
    sps[4] = rotate((s0 + s1) / 2);

    Vec2 t0 = {9999, 9999};
    Vec2 t1 = {-9999, -9999};
    Vec2 tps[5];
    for (int i = 0; i < 4; i++) {
        Vec2 p;
        cin >> p;
        tps[i] = p;
        p = rotate(p);
        t0.x = min(t0.x, p.x);
        t0.y = min(t0.y, p.y);
        t1.x = max(t1.x, p.x);
        t1.y = max(t1.y, p.y);
    }
    tps[4] = unrotate((t0 + t1) / 2);

    for (int i = 0; i < 5; i++) {
        if (is_in_rect(t0, t1, sps[i]) || is_in_rect(s0, s1, tps[i])) {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
}
