// https://matcomgrader.com/problem/9635/build-the-perfect-house/

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

typedef double T;
const T EPS = 1e-6;

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
    bool operator!=(P r) const { return abs(x - r.x) > EPS && abs(y - r.y) > EPS; }

    double angle() const { return atan2(y, x); }
    static P from_angle(double a) { return {cos(a), sin(a)}; }
};

// a segment or an infinite line
// does not handle point segments correctly!
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
    bool seg_collide(L r) const {
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

    // check if this ray and the given segment intersect
    bool ray_seg_collide(L r) const {
        T z = d / r.d;
        if (abs(z) <= EPS) {
            if (abs(side(r.o)) > EPS) return false;
            T s = (r.o - o) * d, e = s + r.d * d;
            if (s > e) swap(s, e);
            return e >= -EPS;
        }
        T s = inter(r), t = -r.inter(*this);
        if (z < 0) s = -s, t = -t, z = -z;
        return s >= -EPS && t >= -EPS && t <= z + EPS;
    }

    // full segment intersection
    // produces a point segment if the intersection is a point
    // however it **does not** handle point segments as input!
    bool seg_inter(L r, L *out) const {
        T z = d / r.d;
        if (abs(z) <= EPS) {
            if (abs(side(r.o)) > EPS) return false;
            if (r.d * d < 0) r = {r.o + r.d, -r.d};
            P s = o * d < r.o * d ? r.o : o;
            P e = (o + d) * d < (r.o + r.d) * d ? o + d : r.o + r.d;
            if (s * d > e * d) return false;
            return *out = L(s, e - s), true;
        }
        T s = inter(r), t = -r.inter(*this);
        if (z < 0) s = -s, t = -t, z = -z;
        if (s >= -EPS && s <= z + EPS && t >= -EPS && t <= z + EPS)
            return *out = L(o + d * s / z, P()), true;
        return false;
    }

    // check if the given point is on the segment
    bool point_on_seg(P r) const {
        if (abs(side(r)) > EPS) return false;
        if ((r - o) * d < -EPS) return false;
        if ((r - o - d) * d > EPS) return false;
        return true;
    }

    // get the point in this line that is closest to a given point
    P closest_to(P r) const { return r + (o - r) * d.rot() * d.rot() / d.magsq(); }
};

struct C {
    P o;
    T r;

    C(P o, T r) : o(o), r(r) {}
    C() : C(P(), T()) {}

    // intersects the circle with a line, assuming they intersect
    // the intersections are sorted with respect to the direction of the line
    pair<P, P> line_inter(L l) const {
        P c = l.closest_to(o);
        T c2 = (c - o).magsq();
        P e = sqrt(max(r * r - c2, T())) * l.d.unit();
        return {c - e, c + e};
    }

    // checks whether the given line collides with the circle
    // negative: 2 intersections
    // zero: 1 intersection
    // positive: 0 intersections
    // UNTESTED but very simple
    T line_collide(L l) const {
        T c2 = (l.closest_to(o) - o).magsq();
        return c2 - r * r;
    }

    // calculates the two intersections between two circles
    // the circles must intersect in one or two points!
    // REALLY UNTESTED
    pair<P, P> inter(C h) const {
        h.o = h.o - o;
        return h.line_inter({(1 + (r * r - h.r * h.r) / h.o.magsq()) / 2 * h.o, h.o.rot()});
    }

    // check if the given circles intersect
    bool collide(C h) const {
        return (h.o - o).magsq() <= (h.r + r) * (h.r + r);
    }

    // get one of the two tangents that cross through the point
    // the point must not be inside the circle
    // a = -1: cw (relative to the circle) tangent
    // a =  1: ccw (relative to the circle) tangent
    P point_tangent(P p, T a) const {
        T c = r * r / p.magsq();
        return o + c * (p - o) - a * sqrt(c * (1 - c)) * (p - o).rot();
    }

    // get one of the 4 tangents between the two circles
    // a =  1: exterior tangents
    // a = -1: interior tangents (requires no area overlap)
    // b =  1: ccw tangent
    // b = -1: cw tangent
    // the line origin is on this circumference, and the direction
    // is a unit vector towards the other circle
    L tangent(C c, T a, T b) const {
        T dr = a * r - c.r;
        P d = c.o - o;
        P n = (d * dr + b * d.rot() * sqrt(d.magsq() - dr * dr)).unit();
        return {o + n * r, -b * n.rot()};
    }

    // find the circumcircle of the given **non-degenerate** triangle
    static C thru_points(P a, P b, P c) {
        P p = L((a + b) / 2, (b - a).rot()).intersection(L((a + c) / 2, (c - a).rot()));
        return {p, (p - a).mag()};
    }

    // find the two circles that go through the given point, are tangent
    // to the given line and have radius `r`
    // the point-line distance must be at most `r`!
    // the circles are sorted in the direction of the line
    static pair<C, C> thru_point_line_r(P a, L t, T r) {
        P d = t.d.rot().unit();
        if (d * (a - t.o) < 0) d = -d;
        auto p = C(a, r).line_inter({t.o + d * r, t.d});
        return {{p.first, r}, {p.second, r}};
    }

    // find the two circles that go through the given points and have radius `r`
    // the circles are sorted by angle with respect to the first point
    // the points must be at most at distance `r`!
    static pair<C, C> thru_points_r(P a, P b, T r) {
        auto p = C(a, r).line_inter({(a + b) / 2, (b - a).rot()});
        return {{p.first, r}, {p.second, r}};
    }
};

// obtain the convex polygon that results from intersecting the given list
// of halfplanes, represented as lines that allow their left side
// assumes the halfplane intersection is bounded
vector<P> halfplane_intersect(vector<L> &H) {
    // L bb(P(-INF, -INF), P(INF, 0));
    // rep(k, 4) H.push_back(bb), bb.o = bb.o.rot(), bb.d = bb.d.rot();

    sort(H.begin(), H.end(), [](L a, L b) { return a.d.angcmp(b.d) < 0; });
    deque<L> q;
    int n = 0;
    rep(i, H.size()) {
        while (n >= 2 && H[i].side(q[n - 1].intersection(q[n - 2])) > 0)
            q.pop_back(), n--;
        while (n >= 2 && H[i].side(q[0].intersection(q[1])) > 0)
            q.pop_front(), n--;
        if (n > 0 && H[i].parallel(q[n - 1])) {
            if (H[i].d * q[n - 1].d < 0) return {};
            if (H[i].side(q[n - 1].o) > 0) q.pop_back(), n--;
            else continue;
        }
        q.push_back(H[i]), n++;
    }

    while (n >= 3 && q[0].side(q[n - 1].intersection(q[n - 2])) > 0)
        q.pop_back(), n--;
    while (n >= 3 && q[n - 1].side(q[0].intersection(q[1])) > 0)
        q.pop_front(), n--;
    if (n < 3) return {};

    vector<P> ps(n);
    rep(i, n) ps[i] = q[i].intersection(q[(i + 1) % n]);
    return ps;
}

// get the area of a polygon in ccw order
// returns negative area for cw polygons
T area2(const vector<P> &ps) {
    int N = ps.size();
    T a = 0;
    rep(i, N) a += (ps[i] - ps[0]) / (ps[(i + 1) % N] - ps[i]);
    return a;
}

// get the convex hull with the least amount of vertices for the given set of points.
// probably misbehaves if points are not distinct!
vector<P> convex_hull(vector<P> &ps) {
    int N = ps.size(), n = 0, k = 0;
    if (N <= 2) return ps;
    rep(i, N) if (make_pair(ps[i].y, ps[i].x) < make_pair(ps[k].y, ps[k].x)) k = i;
    swap(ps[k], ps[0]);
    sort(++ps.begin(), ps.end(), [&](P l, P r) {
        T x = (r - l) / (ps[0] - l), d = (r - l) * (ps[0] - l);
        return x > 0 || x == 0 && d < 0;
    });

    vector<P> H;
    for (P p : ps) {
        while (n >= 2 && (H[n - 1] - p) / (H[n - 2] - p) >= 0) H.pop_back(), n--;
        H.push_back(p), n++;
    }
    return H;
}

/*
// Naive but slow solution
int N;
vector<P> A;

double sq(double x) { return x * x; }

bool can_build(double R) {
    bool allok = false;
    for (P p : A) {
        if (p.magsq() < sq(R + EPS)) return false;
        for (double k = -1; k <= 1; k += 2) {
            P q = C(P(), R).point_tangent(p, k).unit();
            bool ok = true;
            for (P r : A) {
                if (abs(q * r) < R - EPS && abs(q / r) < R - EPS) {
                    ok = false;
                }
            }
            allok |= ok;
        }
    }
    cerr << "radius " << R << ": " << allok << endl;
    return allok;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i];

    double l = 0, r = 1e10;
    rep(iter, 100) {
        double m = (l + r) / 2;
        if (can_build(m)) l = m;
        else r = m;
    }

    cout << fixed << setprecision(4) << 8 * l << endl;
}
*/

int N;
vector<P> A;

double sq(double x) { return x * x; }

bool can_build(double R) {
    bool allok = false;
    for (P p : A) {
        if (p.magsq() < sq(R + EPS)) return false;
        for (double k = -1; k <= 1; k += 2) {
            P q = C(P(), R).point_tangent(p, k).unit();
            bool ok = true;
            for (P r : A) {
                if (abs(q * r) < R - EPS && abs(q / r) < R - EPS) {
                    ok = false;
                }
            }
            allok |= ok;
        }
    }
    cerr << "radius " << R << ": " << allok << endl;
    return allok;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i];

    sort(A.begin(), A.end(), [](P a, P b) {
        return a.angcmp(b) < 0;
    });

    double l = 0, r = 1e10;
    rep(iter, 100) {
        double m = (l + r) / 2;
        if (can_build(m)) l = m;
        else r = m;
    }

    cout << fixed << setprecision(4) << 8 * l << endl;
}