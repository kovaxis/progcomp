// http://acmgnyr.org/year2005/f.pdf
// https://bacs.cs.istu.ru/submit.php?pid=2046

#pragma GCC optimize("O0")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (1) cerr

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

    // find the circumcircle of the given **non-degenerate** triangle
    static C thru_points(P a, P b, P c) {
        P p = L((a + b) / 2, (b - a).rot()).intersection(L((a + c) / 2, (c - a).rot()));
        return {p, (p - a).mag()};
    }

    // intersects the circle with a line
    // returns the number of intersections
    // places intersection in `out`
    // needs space in `out` for at most 2 intersections
    // SEMITESTED
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

    // check if the given circles intersect
    bool collide(C h) const {
        return (h.o - o).magsq() <= (h.r + r) * (h.r + r);
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

P on_top(P l, P r) {
    P d = (r - l) / 2;
    double R = 1.;
    return (l + r) / 2 + d.rot().unit() * sqrt(4 * R * R - d.magsq());
}

void printnum(double x) {
    cerr << "printing " << fixed << setw(20) << setprecision(20) << x << " as " << fixed << setw(4) << setprecision(4) << x / 1. << endl;
    cout << fixed << setw(4) << setprecision(4) << x / 1.;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        int N;
        cin >> N;
        vector<vector<P>> rows(N, vector<P>(N));
        rep(j, N) cin >> rows[0][j].x;
        // rep(j, N) rows[0][j].x = floor(rows[0][j].x * 10000 + 0.5);
        rep(j, N) rows[0][j].y = 1;
        sort(rows[0].begin(), rows[0].end(), [](P a, P b) { return a.x < b.x; });

        repx(i, 1, N) {
            rep(j, N - i) {
                rows[i][j] = on_top(rows[i - 1][j], rows[i - 1][j + 1]);
            }
        }

        P ans = P((rows[0][0].x + rows[0][N - 1].x) / 2, rows[N - 1][0].y);
        ans = rows[N - 1][0];

        cout << setw(0) << tc + 1 << ": ";
        printnum(ans.x);
        cout << " ";
        printnum(ans.y);
        cout << "\n";
    }
}
