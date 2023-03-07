// https://projecteuler.net/problem=587

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

typedef double T;
const T EPS = 0;

struct P {
    T x, y;

    P(T x, T y) : x(x), y(y) {}
    P() : P(0, 0) {}

    friend ostream &operator<<(ostream &s, const P &r) {
        return s << r.x << " " << r.y;
    }
    friend istream &operator>>(istream &s, P &r) { return s >> r.x >> r.y; }

    P operator+(P r) const { return {x + r.x, y + r.y}; }
    P operator-(P r) const { return {x - r.x, y - r.y}; }
    P operator*(T r) const { return {x * r, y * r}; }
    P operator/(T r) const { return {x / r, y / r}; }
    P operator-() const { return {-x, -y}; }
    friend P operator*(T l, P r) { return {l * r.x, l * r.y}; }

    P rot() const { return {-y, x}; }
    T operator*(P r) const { return x * r.x + y * r.y; }
    T operator/(P r) const { return rot() * r; }

    T magsq() const { return x * x + y * y; }
    T mag() const { return sqrt(magsq()); }
    P unit() const { return *this / mag(); }

    bool half() const { return abs(y) <= EPS && x < -EPS || y < -EPS; }
    T angcmp(P r) const {
        int h = (int)half() - r.half();
        return h ? h : r / *this;
    }

    bool operator==(P r) const { return abs(x - r.x) <= EPS && abs(y - r.y) <= EPS; }
};

// a segment or an infinite line
// does not handle point segments
struct L {
    P o, d;

    L() : o(), d() {}
    L(P o, P d) : o(o), d(d) {}

    // UNTESTED
    L(P ab, T c) : d(ab.rot()), o(ab * -c / ab.magsq()) {}
    pair<P, T> line_eq() { return {-d.rot(), d.rot() * o}; }

    // returns a number indicating which side of the line the point is in
    // negative: left
    // positive: right
    T side(P r) const { return (r - o) / d; }

    // returns the intersection coefficient
    // in the range [0, d / r.d]
    // if d / r.d is zero, the lines are parallel
    T inter(L r) const { return (r.o - o) / r.d; }

    // get the single intersection point
    // lines must not be parallel
    P intersection(L r) const { return o + d * inter(r) / (d / r.d); }

    // check if lines are parallel
    bool parallel(L r) const { return abs(d / r.d) <= EPS; }

    // check if segments intersect
    // UNTESTED
    bool seg_inter(L r) const {
        T z = d / r.d;
        if (abs(z) <= EPS) {
            if (abs(side(r.o)) > EPS) return false;
            T s = (r.o - o) * d, e = s + r.d * d;
            if (s > e) swap(s, e);
            return s <= d * d + EPS && e >= -EPS;
        }
        T s = inter(r), t = -r.inter(*this);
        if (z < 0) s = -s, t = -t, z = -z;
        return s >= -EPS && s <= z + EPS && t >= -EPS && t <= z + EPS;
    }

    // check if this segment intersects the given ray
    // UNTESTED
    bool segray_inter(L r) const {
        T z = d / r.d;
        if (abs(z) <= EPS) {
            if (abs(side(r.o)) > EPS) return false;
            T s = (r.o - o) * d;
            return r.d * d < 0 ? s >= -EPS : s <= d * d + EPS;
        }
        T s = inter(r), t = -r.inter(*this);
        if (z < 0) s = -s, t = -t, z = -z;
        return s >= -EPS && s <= z + EPS && t >= -EPS;
    }

    // get the point in this line that is closest to a given point
    // UNTESTED
    P closest_to(P r) const { return r + (o - r) * d.rot() * d.rot() / d.magsq(); }
};

struct C {
    P o;
    T r;

    // intersects the circle with a line
    // returns the number of intersections
    // places intersection in `out`
    // needs space in `out` for at most 2 intersections
    // UNTESTED
    int line_inter(L l, P *out) const {
        P c = l.closest_to(o);
        T c2 = (c - o).magsq();
        if (c2 > r * r) return 0;
        if (c2 == r * r) return out[0] = c, 1;
        P e = sqrt(r * r - c2) * l.d.unit();
        return out[0] = c - e, out[1] = c + e, 2;
    }

    // calculates the intersections between two circles
    // returns results the same way as `line_inter`
    // the circles must not be concentric
    // UNTESTED
    int inter(C h, P *out) const {
        L l(-2 * (o - h.o), (o - h.o).magsq() + h.r * h.r - r * r);
        return h.o = {}, h.line_inter(l, out);
    }

    // get the two tangent points between a circle and a point
    // the point must not be inside the circle
    // UNTESTED
    pair<P, P> tangents(P p) const {
        p = p - o;
        T c = r * r / p.magsq();
        P m = o + c * p;
        P x = sqrt(c * (1. - c)) * p.rot();
        return {m - x, m + x};
    }
};

double calcarea(int n) {
    P inter[2];
    int inter_cnt = C{P(1, 1), 1}.line_inter(L(P(0, 0), P(n, 1)), inter);
    assert(inter_cnt == 2);
    P p = inter[0];

    return p.y / 2. + (1. - p.x) / 2. - asin(1. - p.x) / 2.;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    double larea = (4. - M_PI) / 4.;
    repx(n, 1, 1e9) {
        double p = calcarea(n) / larea;
        cout << "n = " << n << ": " << p * 100. << "%" << endl;
        if (p < 0.001) break;
    }
}
