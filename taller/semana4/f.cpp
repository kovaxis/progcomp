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
    static Vec2 from_angle(T angle) { return {(T)cos(angle), (T)sin(angle)}; }
};

struct Circle {
    Vec2 o;
    T r;
};

/// Find the pair of tangent points on circumference `c` to point `p`.
/// That is, find the tangent lines that cross point `p` and intersect the
/// circumference `c`, and return the points where these lines intersect `c`.
///
/// The first point returned is the counterclockwise tangent, followed by the
/// clockwise tangent.
///
/// If the point is inside the circle, NaN is returned.
pair<Vec2, Vec2> tangents(Circle c, Vec2 p) {
    Vec2 d = p - c.o;
    T r2d2 = c.r * c.r / d.magsq();
    Vec2 mid = c.o + r2d2 * d;
    Vec2 dif = sqrt(r2d2 * (1. - r2d2)) * d.rotated();
    return {mid + dif, mid - dif};
}

double angle(double a) {
    while (a <= -M_PI) {
        a += 2 * M_PI;
    }
    while (a > M_PI) {
        a -= 2 * M_PI;
    }
    return a;
}

static Vec2 target;
static double v, w;

const double PI = 3.14159265358979323846;

double time_in_flight(double start_angle, double ccw) {
    double r = v / w;
    Vec2 o = Vec2::from_angle(start_angle + PI / 2 * ccw);
    Vec2 d = target - o;
    T r2d2 = r * r / d.magsq();
    Vec2 mid = c.o + r2d2 * d;
    Vec2 dif = sqrt(r2d2 * (1. - r2d2)) * d.rotated();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> target;
    cin >> v;
    cin >> w;

    double dist = target.mag();
    double halfdist = dist / 2.;
    double launch_angle = asin(min(halfdist / r, 1.));
    double straight_angle = target.angle();

    double spin = 0.;
    double dist = 0.;
    if (straight_angle - launch_angle > 0. ||
        straight_angle + launch_angle < 0.) {
        spin += min(angle(straight_angle + launch_angle - 0.),
                    angle(straight_angle - launch_angle - 0.));
    }
    if (halfdist > r) {
        double missing = dist - r;
        dist += sqrt(missing * missing - r * r);
    } else {
        spin += launch_angle * 2;
    }
}
