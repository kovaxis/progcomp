// https://acm.timus.ru/problem.aspx?space=1&num=1504

#pragma GCC optimize("Ofast")
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
    bool operator<(P r) const { return make_pair(x, y) < make_pair(r.x, r.y); }

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

const T INF = 1e18;

typedef ll lll; // if all coordinates are < 2e4
// typedef __int128_t lll; // if on a 64-bit platform

struct Q {
    Q *rot, *o;
    P p = {INF, INF};
    bool mark;
    P &F() { return r()->p; }
    Q *&r() { return rot->rot; }
    Q *prev() { return rot->o->rot; }
    Q *next() { return r()->prev(); }
};

T cross(P a, P b, P c) {
    return (b - a) / (c - a);
}

bool circ(P p, P a, P b, P c) { // is p in the circumcircle?
    lll p2 = p.magsq(), A = a.magsq() - p2,
        B = b.magsq() - p2, C = c.magsq() - p2;
    return cross(p, a, b) * C + cross(p, b, c) * A + cross(p, c, a) * B > 0;
}

Q *makeEdge(Q *&H, P orig, P dest) {
    Q *r = H ? H : new Q{new Q{new Q{new Q{0}}}};
    H = r->o;
    r->r()->r() = r;
    repx(i, 0, 4) r = r->rot, r->p = {INF, INF}, r->o = i & 1 ? r : r->r();
    r->p = orig;
    r->F() = dest;
    return r;
}

void splice(Q *a, Q *b) {
    swap(a->o->rot->o, b->o->rot->o);
    swap(a->o, b->o);
}

Q *connect(Q *&H, Q *a, Q *b) {
    Q *q = makeEdge(H, a->F(), b->p);
    splice(q, a->next());
    splice(q->r(), b);
    return q;
}

pair<Q *, Q *> rec(Q *&H, const vector<P> &s) {
    if (s.size() <= 3) {
        Q *a = makeEdge(H, s[0], s[1]), *b = makeEdge(H, s[1], s.back());
        if (s.size() == 2) return {a, a->r()};
        splice(a->r(), b);
        auto side = cross(s[0], s[1], s[2]);
        Q *c = side ? connect(H, b, a) : 0;
        return {side < 0 ? c->r() : a, side < 0 ? c : b->r()};
    }

#define J(e) e->F(), e->p
#define valid(e) (cross(e->F(), J(base)) > 0)
    Q *A, *B, *ra, *rb;
    int half = s.size() / 2;
    tie(ra, A) = rec(H, {s.begin(), s.end() - half});
    tie(B, rb) = rec(H, {s.begin() + s.size() - half, s.end()});
    while ((cross(B->p, J(A)) < 0 && (A = A->next())) ||
           (cross(A->p, J(B)) > 0 && (B = B->r()->o)))
        ;
    Q *base = connect(H, B->r(), A);
    if (A->p == ra->p) ra = base->r();
    if (B->p == rb->p) rb = base;

#define DEL(e, init, dir)                            \
    Q *e = init->dir;                                \
    if (valid(e))                                    \
        while (circ(e->dir->F(), J(base), e->F())) { \
            Q *t = e->dir;                           \
            splice(e, e->prev());                    \
            splice(e->r(), e->r()->prev());          \
            e->o = H;                                \
            H = e;                                   \
            e = t;                                   \
        }
    for (;;) {
        DEL(LC, base->r(), o);
        DEL(RC, base, prev());
        if (!valid(LC) && !valid(RC)) break;
        if (!valid(LC) || (valid(RC) && circ(J(RC), J(LC))))
            base = connect(H, RC, base->r());
        else
            base = connect(H, base->r(), LC->r());
    }
    return {ra, rb};
#undef J
#undef valid
#undef DEL
}

// there must be no duplicate points
// returns no triangles in the case of all collinear points
// produces counter-clockwise triangles ordered in triples
// maximizes the minimum angle across all triangulations
// the euclidean mst is a subset of these edges
// O(N log N)
vector<P> triangulate(vector<P> pts) {
    sort(pts.begin(), pts.end(), [](P a, P b) {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    });
    assert(unique(pts.begin(), pts.end()) == pts.end());
    if (pts.size() < 2) return {};
    Q *H = 0;
    Q *e = rec(H, pts).first;
    vector<Q *> q = {e};
    int qi = 0;
    while (cross(e->o->F(), e->F(), e->p) < 0) e = e->o;
#define ADD                      \
    {                            \
        Q *c = e;                \
        do {                     \
            c->mark = 1;         \
            pts.push_back(c->p); \
            q.push_back(c->r()); \
            c = c->next();       \
        } while (c != e);        \
    }
    ADD;
    pts.clear();
    while (qi < (int)q.size())
        if (!(e = q[qi++])->mark) ADD;
    return pts;
#undef ADD
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cerr << "reading" << endl;

    ll R, N;
    cin >> R >> N;
    vector<P> A(N);
    map<P, ll> B;
    rep(i, N) {
        ll x;
        cin >> A[i] >> x;
        B[A[i]] = x;
    }

    cerr << "triangulating" << endl;

    vector<P> tris = triangulate(A);
    map<P, map<P, int>> E;

    cerr << "triangulated" << endl;

    for (int i = 0; i < tris.size(); i += 3) {
        E[tris[i + 0]][tris[i + 1]] += 1, E[tris[i + 0]][tris[i + 2]] += 1;
        E[tris[i + 1]][tris[i + 0]] += 1, E[tris[i + 1]][tris[i + 2]] += 1;
        E[tris[i + 2]][tris[i + 0]] += 1, E[tris[i + 2]][tris[i + 1]] += 1;
    }

    cerr << "built adjacency" << endl;

    vector<pair<P, P>> good;
    if (tris.empty()) {
        cerr << "filtering collinear" << endl;
        P d = (A[1] - A[0]).rot();
        for (P p : A) {
            good.push_back({p, C(P(), R).line_inter({p, d}).second});
        }
    }
    for (auto &pr : E) {
        P p = pr.first;
        vector<P> adj(pr.second.begin(), pr.second.end());
        cerr << "filtering point " << p << endl;
        sort(adj.begin(), adj.end(), [&](P a, P b) {
            return (a - p).angcmp(b - p) < 0;
        });
        bool alljoined = true;
        P d;
        if (adj.size() <= 2) {
            for (P a : adj) d = d + (p - a);
            alljoined = false;
        }
        rep(i, adj.size()) {
            int j = (i + 1) % adj.size();
            cerr << "  checking adjacents " << adj[i] << " and " << adj[j] << endl;
            if (E[adj[i]][adj[j]] < 2) {
                cerr << "    not connected" << endl;
                alljoined = false;
                d = adj[i] - p + adj[j] - p;
                if ((adj[i] - p) / (adj[j] - p) < 0) d = -d;
            }
        }
        if (!alljoined) {
            cerr << "intersecting " << p << " with dir " << d << " with circle" << endl;
            P e = C(P(), R).line_inter({p, d}).second;
            good.push_back({p, e});
        }
    }
    cerr << "filtered, with " << good.size() << " points remaining" << endl;

    sort(good.begin(), good.end(), [&](auto a, auto b) {
        return B[a.first] > B[b.first];
    });

    cout << fixed << setprecision(9) << good[0].second << endl;
}
