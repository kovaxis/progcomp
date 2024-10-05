#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

typedef double T;
const T INF = 1e9;

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
    P norm() const { return *this / mag(); }

    bool half() const { return y == 0 && x < 0 || y < 0; }
    bool angle_lt(P r) const {
        return half() == r.half() ? rot() * r > 0 : half() < r.half();
    }
};

// a segment or an infinite line
// does not handle point segments
struct L {
    P o, d;

    L() : o(), d() {}
    L(P o, P d) : o(o), d(d) {}
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
    bool parallel(L r) const { return d / r.d == 0; }

    // check if segments intersect
    bool seg_inter(L r) const {
        T z = d / r.d;
        if (z == 0) {
            if ((r.o - o) / d) return false;
            T s = (r.o - o) * d, e = s + r.d * d;
            if (s > e) swap(s, e);
            return s <= d * d && e >= 0;
        }
        T s = inter(r), t = -r.inter(*this);
        if (z < 0) s = -s, t = -t, z = -z;
        return 0 <= s && s <= z && 0 <= t && t <= z;
    }

    // check if this segment intersects the given ray
    bool segray_inter(L r) const {
        T z = d / r.d;
        if (z == 0) {
            if ((r.o - o) / d) return false;
            T s = (r.o - o) * d;
            return r.d * d < 0 ? s >= 0 : s <= d * d;
        }
        T s = inter(r), t = -r.inter(*this);
        if (z < 0) s = -s, t = -t, z = -z;
        return 0 <= s && s <= z && 0 <= t;
    }

    L offset(P r) const { return {o + r, d}; }

    // get the closest point to the origin that belongs to this infinite line
    P closest() const { return o * d.rot() * d.rot() / d.magsq(); }
};

// obtain the convex polygon that results from intersecting the given list
// of halfplanes, represented as lines that allow their left side
// assumes the halfplane intersection is bounded
vector<P> halfplane_intersect(vector<L> &H) {
    L bb(P(-INF, -INF), P(INF, 0));
    rep(k, 4) H.push_back(bb), bb.o = bb.o.rot(), bb.d = bb.d.rot();

    sort(H.begin(), H.end(), [](L a, L b) { return a.d.angle_lt(b.d); });
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
T area(const vector<P> &ps) {
    int N = ps.size();
    T a = 0;
    rep(i, N) a += (ps[(i + 1) % N] - ps[i]).rot() * (ps[0] - ps[i]);
    return a / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setw(10) << setprecision(10);

    int N;
    cin >> N;
    vector<P> ps(N);
    rep(i, N) cin >> ps[i];

    vector<L> H(N);
    rep(i, N) H[i] = L(ps[i], ps[i] - ps[(i + 1) % N]);
    vector<P> b = halfplane_intersect(H);

    cout << area(b) << endl;
}
