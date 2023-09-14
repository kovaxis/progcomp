#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef __int128 ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

const double INF = 1e100;

ll abs(ll x) { return x < 0 ? -x : x; }
ostream &operator<<(ostream &s, ll x) { return s << (double)x; }

struct R {
    ll p, q;

    R() : p(0), q(1) {}
    R(ll x) : p(x), q(1) {}
    R(ll p, ll q) : p(p), q(q) {
        assert(q > 0);
        assert(__gcd(abs(p), q) == 1);
    }

    R operator*(R r) const {
        ll bc = __gcd(abs(r.p), q), ad = __gcd(abs(p), r.q);
        R res = {(p / ad) * (r.p / bc), (q / bc) * (r.q / ad)};
        // cerr << p << "/" << q << " x " << r.p << "/" << r.q << " = " << res.p << "/" << res.q << endl;
        // assert((((double)p / q) * ((double)r.p / r.q) - (double)res.p / res.q) <= 1e-10);
        return res;
    }

    R operator/(R r) const {
        assert(r.p != 0);
        return r.p < 0 ? R(-p, q) * R(r.q, -r.p) : R(p, q) * R(r.q, r.p);
    }

    R operator+(R r) const {
        ll g = __gcd(q, r.q);
        ll rp = r.q / g * p + q / g * r.p, rq = q / g * r.q;
        R res = (g = __gcd(abs(rp), rq), R(rp / g, rq / g));
        // cerr << p << "/" << q << " + " << r.p << "/" << r.q << " = " << res.p << "/" << res.q << endl;
        // assert(((double)p / q + (double)r.p / r.q - (double)res.p / res.q) <= 1e-10);
        return res;
    }

    R operator-() const { return {-p, q}; }
    R operator-(R r) const { return *this + -r; }

    bool operator<(R r) const {
        // int128?
        // assert(abs(p) <= ll(1e18) && abs(r.q) <= ll(1e18) && abs(r.p) <= ll(1e18) && abs(q) <= ll(1e18));
        return p * r.q < r.p * q;
    }
    bool operator==(R r) const { return p == r.p && q == r.q; }

    bool operator!=(R r) const { return !(*this == r); }
    bool operator>(R r) const { return r < *this; }
    bool operator<=(R r) const { return !(*this > r); }
    bool operator>=(R r) const { return !(*this < r); }

    friend istream &operator>>(istream &s, R &r) {
        int x;
        s >> x;
        r = x;
        return s;
    }
    friend ostream &operator<<(ostream &s, R r) {
        return s << r.approx();
    }

    double approx() const { return (double)p / q; }
};

struct P {
    R x, y;

    P() : x(0), y(0) {}
    P(R x, R y) : x(x), y(y) {}

    P operator+(P r) const { return {x + r.x, y + r.y}; }
    P operator-(P r) const { return {x - r.x, y - r.y}; }
    P operator-() const { return {-x, -y}; }

    P operator*(R r) const { return {x * r, y * r}; }
    P operator/(R r) const { return {x / r, y / r}; }

    R magsq() const { return x * x + y * y; }

    R operator*(P r) const { return x * r.x + y * r.y; }
    P perp() const { return {-y, x}; }

    friend istream &operator>>(istream &s, P &p) { return s >> p.x >> p.y; }
    friend ostream &operator<<(ostream &s, P p) { return s << p.x << " " << p.y; }

    bool operator==(P r) const { return x == r.x && y == r.y; }
    bool operator!=(P r) const { return !(*this == r); }
};

struct L {
    P o, d;

    R side(P r) const { return (r - o).perp() * d; }

    R inter(L r) const { return (r.o - o).perp() * r.d; }

    // proper segment intersection
    // only detects point intersections that do not occur at the endpoints of r
    bool proper_inter(L r, P *out) const {
        R z = d.perp() * r.d;
        if (z == 0) return false; // skip parallel segments
        R s = inter(r), t = -r.inter(*this);
        if (z < 0) s = -s, t = -t, z = -z;
        if (s >= 0 && s <= z && t > 0 && t < z)
            return *out = o + d * s / z, true;
        return false;
    }

    // get the point in this line that is closest to a given point
    P closest_to(P r) const {
        P dr = d.perp();
        return r + dr * ((o - r) * dr / d.magsq());
    }

    bool point_on_seg(P r) const {
        if (side(r) != 0) return false;
        if ((r - o) * d < 0) return false;
        if ((r - o - d) * d > 0) return false;
        return true;
    }
};

int N;
vector<P> A;
vector<vector<double>> D;
vector<bool> stargaze;

P vert(int i) { return A[(i + N) % N]; }

int signum(R x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

// warning! a and b should be meaningfully distinct!
template <class OP>
void collide(P a, P b, OP op) {
    L seg = {a, b - a};
    assert(seg.d != P(0, 0));
    rep(i, N) {
        L edge = {vert(i), vert(i + 1) - vert(i)};

        P inter;
        if (!seg.proper_inter(edge, &inter)) continue;
        // proper intersection
        op(inter, true, true);
    }
    rep(i, N) {
        if (!seg.point_on_seg(vert(i))) continue;
        int prv = signum((vert(i - 1) - a).perp() * (b - a));
        int nxt = signum((vert(i + 1) - a).perp() * (b - a));
        int cnv = signum((vert(i + 1) - vert(i)).perp() * (vert(i) - vert(i - 1)));
        op(vert(i),
           cnv > 0 ? nxt < 0 || (nxt == 0 && prv < 0) : prv > 0 || nxt < 0,
           cnv > 0 ? prv > 0 || (prv == 0 && nxt > 0) : prv > 0 || nxt < 0);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    A.resize(N + 2);
    rep(i, N + 2) cin >> A[i];

    D.assign(N + 2, vector<double>(N + 2, INF));
    rep(u, N + 2) D[u][u] = 0;

    stargaze.assign(N + 2, false);
    rep(u, N + 2) rep(v, N + 2) {
        if (u == v) continue;

        bool L = false, R = false;
        bool Ls = false, Rs = false;
        collide(A[u], A[v], [&](P c, bool l, bool r) {
            if (c == A[u] && !(l && r)) return;
            Ls |= l, Rs |= r;
            if (c == A[v]) return;
            L |= l, R |= r;
        });
        if (L && R) continue;

        // an entire side of v can be seen from u
        D[u][v] = sqrt((A[v] - A[u]).magsq().approx());
        cerr << "point " << A[u] << " can see " << A[v] << " with dist " << D[u][v] << endl;

        if (u == N + 1 && !(Ls && Rs)) {
            stargaze[v] = true;
            cerr << "point " << A[v] << " can stargaze" << endl;
        }
    }

    rep(u, N + 2) {
        if (D[u][N + 1] < INF) {
            D[u][N + 1] = 0;
            cerr << "point " << A[u] << " can see the star" << endl;
        }
    }

    rep(u, N + 1) rep(v, N + 1) {
        if (u == v) continue;
        if (!stargaze[v]) continue;

        P a = A[u], b = A[v];
        L starb = {A[N + 1], b - A[N + 1]};
        P x = starb.closest_to(a);
        if (x == a) continue;
        if ((x - b) * starb.d <= 0) continue;
        P y = x;
        collide(b, x, [&](P c, bool l, bool r) {
            if (c == b) return;
            if ((c - b).magsq() < (y - b).magsq()) y = c;
        });
        // cerr << "potential starline from " << A[u] << " against " << A[v] << " at " << y << endl;
        bool L = false, R = false;
        collide(a, y, [&](P c, bool l, bool r) {
            if (c == a && !(l && r)) return;
            if (c == y) return;
            cerr << "type " << l << r << " collision at " << c << endl;
            L |= l, R |= r;
        });
        if (L && R) continue;
        double dist = sqrt((a - y).magsq().approx());
        D[u][N + 1] = min(D[u][N + 1], dist);
        cerr << "point " << A[u] << " can see a star-line at intersection against " << A[v] << " at " << y << " with dist " << dist << endl;
    }

    rep(k, N + 2) rep(u, N + 2) rep(v, N + 2) D[u][v] = min(D[u][v], D[u][k] + D[k][v]);

    cout << fixed << setprecision(12) << D[N][N + 1] << endl;
}
