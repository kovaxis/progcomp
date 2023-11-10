#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

typedef double T;

struct P {
    T x, y;
    int i;

    P operator+(P r) const { return {x + r.x, y + r.y}; }
    P operator-(P r) const { return {x - r.x, y - r.y}; }
    P operator*(T r) const { return {x * r, y * r}; }
    P operator/(T r) const { return {x / r, y / r}; }

    P perp() const { return {-y, x}; }
    T operator*(P r) const { return x * r.x + y * r.y; }
    T operator%(P r) const { return perp() * r; }

    T magsq() { return x * x + y * y; }

    bool operator==(P r) const { return x == r.x && y == r.y; }
};

struct L {
    P o, d;

    P closest_to(P r) {
        P dr = d.perp();
        return r + dr * ((o - r) * dr) / d.magsq();
    }
};

const T INF = 1e18;

typedef ll lll; // if all coordinates are < 2e4
// typedef __int128_t lll; // if on a 64-bit platform

#define J(e) e->F(), e->p
struct Q {
    Q *rot, *o;
    P p = {INF, INF};
    bool mark;
    P &F() { return r()->p; }
    Q *&r() { return rot->rot; }
    Q *prev() { return rot->o->rot; }
    Q *next() { return r()->prev(); }
};

T cross(P a, P b, P c) { return (b - a) % (c - a); }

bool circ(P p, P a, P b, P c) { // is p in the circumcircle?
    lll p2 = p.magsq(), A = a.magsq() - p2,
        B = b.magsq() - p2, C = c.magsq() - p2;
    return cross(p, a, b) * C + cross(p, b, c) * A + cross(p, c, a) * B > 0;
}

Q *makeEdge(Q *&H, P orig, P dest) {
    Q *r = H ? H : new Q{new Q{new Q{new Q{0}}}};
    H = r->o;
    r->r()->r() = r;
    rep(i, 4) r = r->rot, r->p = {INF, INF}, r->o = i & 1 ? r : r->r();
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

    int half = s.size() / 2;
    auto [ra, A] = rec(H, {s.begin(), s.end() - half});
    auto [B, rb] = rec(H, {s.end() - half, s.end()});
    while ((cross(B->p, J(A)) < 0 && (A = A->next())) ||
           (cross(A->p, J(B)) > 0 && (B = B->r()->o))) {}
    Q *base = connect(H, B->r(), A);
    if (A->p == ra->p) ra = base->r();
    if (B->p == rb->p) rb = base;
    auto valid = [&](Q *e) { return cross(e->F(), J(base)) > 0; };
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
        else base = connect(H, base->r(), LC->r());
    }
    return {ra, rb};
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
    auto add = [&]() {
        Q *c = e;
        do {
            c->mark = 1;
            pts.push_back(c->p);
            q.push_back(c->r());
            c = c->next();
        } while (c != e);
    };
    add();
    pts.clear();
    while (qi < (int)q.size())
        if (!(e = q[qi++])->mark) add();
    return pts;
}

int N;
vector<P> A, centers;

const double EPS = 1e-8;

int signum(double x) {
    if (abs(x) <= EPS) return 0;
    return x > 0 ? 1 : -1;
}

int in_poly(const vector<P> &p, P q) {
    int w = 0;
    rep(i, (int)p.size()) {
        P a = p[i], b = p[(i + 1) % p.size()];
        int k = signum((b - a) % (q - a));
        int u = signum(a.y - q.y), v = signum(b.y - q.y);
        if (k > 0 && u < 0 && v >= 0) w++;
        if (k < 0 && v < 0 && u >= 0) w--;
        if (k == 0 && (q - a) * (q - b) <= 0) return 0;
    }
    return w ? 1 : -1;
}

P circumcenter(P a, P b, P c) {
    b = b - a, c = c - a;
    P p = (b * c.magsq() - c * b.magsq()).perp() / (b % c * 2);
    return a + p;
}

bool circle_line(L l, P o, T r, pair<P, P> &out) {
    P c = l.closest_to(o);
    T c2 = (c - o).magsq();
    T r2 = r * r - c2;
    if (r2 < 0) return false;
    P e = l.d * sqrt(r2 / l.d.magsq());
    out = {c - e, c + e};
    return true;
}

vector<clock_t> ts;
int ts_i;
void t() {
    clock_t t = clock();
    ts[ts_i] += t;
    ts[++ts_i] -= t;
}

bool is_covered(double R) {
    for (P p : centers) {
        bool near = false;
        rep(i, N) {
            T d2 = (p - A[i]).magsq();
            if (d2 <= R * R) near = true;
        }
        if (!near) return false;
    }

    ts.resize(10, 0);

    vector<pair<double, int>> ev;
    ev.reserve(2 * N + 2);
    rep(i, N) {
        P a = A[i], b = A[(i + 1) % N];
        L line = L{a, b - a};

        ts_i = 0;
        t();
        ev.clear();
        T mag2inv = 1 / line.d.magsq();
        for (P vert : A) {
            double l, r;
            {
                T fw = line.d * (vert - line.o) * mag2inv;
                T sd = line.d.perp() * (vert - line.o) * mag2inv;
                T e2 = R * R * mag2inv - sd * sd;
                if (e2 < 0) continue;
                T e = sqrt(e2);
                l = fw - e, r = fw + e;
            }

            l = max(0.0, l), r = min(1.0, r);
            if (l >= r) continue;
            ev.push_back({l, -1});
            if (r < 1) ev.push_back({r, 1});
        }
        ev.push_back({0, 1});
        t();
        sort(ev.begin(), ev.end());
        t();

        int acc = 0;
        for (auto [t, d] : ev) {
            acc += d;
            if (acc > 0) return false;
        }
        t();
    }

    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i].x >> A[i].y;
    rep(i, N) A[i].i = i;

    vector<P> tris = triangulate(A);
    rep(i, (int)tris.size() / 3) {
        P a = tris[i * 3], b = tris[i * 3 + 1], c = tris[i * 3 + 2];
        P p = circumcenter(a, b, c);
        // cerr << "center " << p.x << " " << p.y << endl;
        if (in_poly(A, p) > 0) centers.push_back(p);
        // else cerr << p.x << " " << p.y << " is outside" << endl;
    }

    double l = 0, r = 1e6;
    rep(iter, 45) {
        double m = (l + r) / 2;
        if (is_covered(m)) r = m;
        else l = m;
    }
    cerr << "build: " << ts[1] / (double)CLOCKS_PER_SEC << endl;
    cerr << "sort: " << ts[2] / (double)CLOCKS_PER_SEC << endl;
    cerr << "exec: " << ts[3] / (double)CLOCKS_PER_SEC << endl;

    cout << fixed << setprecision(12) << l << endl;
}