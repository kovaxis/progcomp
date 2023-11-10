#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point {
    typedef Point P;
    T x, y;
    int i = -1;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream &operator<<(ostream &os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

typedef Point<double> P;
typedef struct Quad *Q;
typedef __int128_t lll;      // (can be ll if coords are < 2e4)
P arb(LLONG_MAX, LLONG_MAX); // not equal to any other point

struct Quad {
    Q rot, o;
    P p = arb;
    bool mark;
    P &F() { return r()->p; }
    Q &r() { return rot->rot; }
    Q prev() { return rot->o->rot; }
    Q next() { return r()->prev(); }
} *H;

bool circ(P p, P a, P b, P c) { // is p in the circumcircle?
    lll p2 = p.dist2(), A = a.dist2() - p2,
        B = b.dist2() - p2, C = c.dist2() - p2;
    return (lll)p.cross(a, b) * C + (lll)p.cross(b, c) * A + (lll)p.cross(c, a) * B > 0;
}
Q makeEdge(P orig, P dest) {
    Q r = H ? H : new Quad{new Quad{new Quad{new Quad{0}}}};
    H = r->o;
    r->r()->r() = r;
    rep(i, 0, 4) r = r->rot, r->p = arb, r->o = i & 1 ? r : r->r();
    r->p = orig;
    r->F() = dest;
    return r;
}
void splice(Q a, Q b) {
    swap(a->o->rot->o, b->o->rot->o);
    swap(a->o, b->o);
}
Q connect(Q a, Q b) {
    Q q = makeEdge(a->F(), b->p);
    splice(q, a->next());
    splice(q->r(), b);
    return q;
}

pair<Q, Q> rec(const vector<P> &s) {
    if (sz(s) <= 3) {
        Q a = makeEdge(s[0], s[1]), b = makeEdge(s[1], s.back());
        if (sz(s) == 2) return {a, a->r()};
        splice(a->r(), b);
        auto side = s[0].cross(s[1], s[2]);
        Q c = side ? connect(b, a) : 0;
        return {side < 0 ? c->r() : a, side < 0 ? c : b->r()};
    }

#define H(e) e->F(), e->p
#define valid(e) (e->F().cross(H(base)) > 0)
    Q A, B, ra, rb;
    int half = sz(s) / 2;
    tie(ra, A) = rec({all(s) - half});
    tie(B, rb) = rec({sz(s) - half + all(s)});
    while ((B->p.cross(H(A)) < 0 && (A = A->next())) ||
           (A->p.cross(H(B)) > 0 && (B = B->r()->o)))
        ;
    Q base = connect(B->r(), A);
    if (A->p == ra->p) ra = base->r();
    if (B->p == rb->p) rb = base;

#define DEL(e, init, dir)                            \
    Q e = init->dir;                                 \
    if (valid(e))                                    \
        while (circ(e->dir->F(), H(base), e->F())) { \
            Q t = e->dir;                            \
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
        if (!valid(LC) || (valid(RC) && circ(H(RC), H(LC))))
            base = connect(RC, base->r());
        else
            base = connect(base->r(), LC->r());
    }
    return {ra, rb};
}

vector<P> triangulate(vector<P> pts) {
    sort(all(pts));
    assert(unique(all(pts)) == pts.end());
    if (sz(pts) < 2) return {};
    Q e = rec(pts).first;
    vector<Q> q = {e};
    int qi = 0;
    while (e->o->F().cross(e->F(), e->p) < 0) e = e->o;
#define ADD                      \
    {                            \
        Q c = e;                 \
        do {                     \
            c->mark = 1;         \
            pts.push_back(c->p); \
            q.push_back(c->r()); \
            c = c->next();       \
        } while (c != e);        \
    }
    ADD;
    pts.clear();
    while (qi < sz(q))
        if (!(e = q[qi++])->mark) ADD;
    return pts;
}

struct L {
    P o, d;

    P closest_to(P r) {
        P dr = d.perp();
        return r + dr * (o - r).dot(dr) / d.dist2();
    }
};

int N;
vector<P> A;
vector<L> missing;

double circ_r(P a, P b, P c) {
    b = b - a, c = c - a;
    P p = (b * c.dist2() - c * b.dist2()).perp() / (b.cross(c) * 2);
    if (b.cross(p) < 0 || c.cross(p) > 0 || (c - b).cross(p - b) < 0) {
        // outside of triangle
        return -1;
    } else {
        // inside triangle
        return sqrt(p.dist2());
    }
}

bool within(int l, int r, int x) {
    if (l < r) {
        return l < x && x < r;
    } else {
        return x < r || l < x;
    }
}

bool circle_line(L l, P o, double r, pair<P, P> &out) {
    P c = l.closest_to(o);
    double c2 = (c - o).dist2();
    double r2 = r * r - c2;
    if (r2 < 0) return false;
    P e = l.d * sqrt(r2 / l.d.dist2());
    out = {c - e, c + e};
    return true;
}

bool is_covered(double R) {
    for (L line : missing) {
        vector<pair<double, int>> ev;
        for (P vert : A) {
            pair<P, P> inter;
            if (!circle_line(line, vert, R, inter)) continue;
            double l = (inter.first - line.o).dot(line.d) / line.d.dist2();
            double r = (inter.second - line.o).dot(line.d) / line.d.dist2();
            l = max(0.0, l), r = min(1.0, r);
            if (l >= r) continue;
            ev.push_back({l, -1});
            ev.push_back({r, 1});
        }
        ev.push_back({0, 1});
        ev.push_back({1, -1});
        sort(ev.begin(), ev.end());
        int acc = 0, ok = true;
        for (auto [t, d] : ev) {
            acc += d;
            if (t == 1) break;
            if (acc > 0) ok = false;
        }
        if (!ok) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    A.resize(N);
    rep(i, 0, N) cin >> A[i].x >> A[i].y;
    rep(i, 0, N) A[i].i = i;

    vector<P> tris = triangulate(A);
    double l = 0, r = 1e9;
    rep(i, 0, (int)tris.size() / 3) {
        P a = tris[i * 3], b = tris[i * 3 + 1], c = tris[i * 3 + 2];
        if (within(a.i, b.i, c.i)) continue;
        double x = circ_r(a, b, c);
        l = max(l, x);
        if (x < 0) rep(j, 0, 3) missing.push_back(L{tris[3 * i + j], tris[3 * i + (j + 1) % 3] - tris[3 * i + j]});
    }

    rep(iter, 0, 60) {
        double m = (l + r) / 2;
        if (is_covered(m)) r = m;
        else l = m;
    }

    cout << fixed << setprecision(12) << l << endl;
}