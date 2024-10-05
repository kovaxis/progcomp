#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

typedef double T;
const T EPS = 1e-8;

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
    bool operator<(P r) const { return make_pair(x, y) < make_pair(r.x, r.y); }

    double angle() const { return atan2(y, x); }
    static P from_angle(double a) { return {cos(a), sin(a)}; }
};

const T INF = 1e18;

typedef double lll;
// typedef ll lll; // if all coordinates are < 2e4
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
// UNTESTED
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

int N;
vector<P> A, B;
map<P, int> toid;

int ansi, ansj;
double ansd;

void check(int i, int j) {
    P a = B[i], b = B[j];
    T d = (a - b).magsq();
    if (d < ansd) {
        ansi = toid[a];
        ansj = toid[b];
        ansd = d;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i];

    rep(i, N) toid[A[i]] = i;

    B = triangulate(A);
    ansd = INFINITY;

    for (int i = 0; i < B.size(); i += 3) {
        // cerr << "triangle " << toid[B[i]] + 1 << " " << toid[B[i + 1]] + 1 << " " << toid[B[i + 2]] + 1 << endl;
        check(i, i + 1);
        check(i + 1, i + 2);
        check(i, i + 2);
    }
    if (B.empty()) {
        B = A;
        sort(B.begin(), B.end());
        rep(i, N - 1) check(i, i + 1);
    }

    if (ansi > ansj) swap(ansi, ansj);
    cout << ansi << " " << ansj << " " << fixed << setprecision(6) << sqrt(ansd) << endl;
}
