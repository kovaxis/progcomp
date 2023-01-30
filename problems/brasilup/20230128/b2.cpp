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

const T INF = 1e9;
const T EPS = 1e-7;

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

    bool half() const { return abs(y) <= EPS && x < -EPS || y < -EPS; }
    bool angle_lt(P r) const {
        return half() == r.half() ? rot() * r > EPS : half() < r.half();
    }

    bool operator<(P r) const { return make_pair(x, y) < make_pair(r.x, r.y); }
    bool operator==(P r) const { return x == r.x && y == r.y; }
};

struct L {
    P o, d;

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
    bool parallel(L r) const { return abs(d / r.d) <= EPS; }

    bool seg_inter(L r) const {
        T z = d / r.d;
        if (abs(z) <= EPS) {
            if ((r.o - o) / d) return false;
            T s = (r.o - o) * d, e = s + r.d * d;
            if (s > e) swap(s, e);
            return s <= d * d + EPS && e >= -EPS;
        }
        T s = inter(r), t = -r.inter(*this);
        if (z < 0) s = -s, t = -t, z = -z;
        return -EPS <= s && s <= z + EPS && -EPS <= t && t <= z + EPS;
    }
};

// obtain the convex polygon that results from intersecting the given list
// of halfplanes, represented as lines that allow their left side.
vector<P> halfplane_intersect(vector<L> &H) {
    L bb(P(-INF, -INF), P(INF, 0));
    rep(k, 4) H.push_back(bb), bb.o = bb.o.rot(), bb.d = bb.d.rot();

    sort(H.begin(), H.end(), [](L a, L b) { return a.d.angle_lt(b.d); });
    deque<L> q;
    int n = 0;
    rep(i, H.size()) {
        while (n >= 2 && H[i].side(q[n - 1].intersection(q[n - 2])) > EPS)
            q.pop_back(), n--;
        while (n >= 2 && H[i].side(q[0].intersection(q[1])) > EPS)
            q.pop_front(), n--;
        if (n > 0 && H[i].parallel(q[n - 1])) {
            if (H[i].d * q[n - 1].d < -EPS) return {};
            if (H[i].side(q[n - 1].o) > EPS) q.pop_back(), n--;
            else continue;
        }
        q.push_back(H[i]), n++;
    }

    while (n >= 3 && q[0].side(q[n - 1].intersection(q[n - 2])) > EPS)
        q.pop_back(), n--;
    while (n >= 3 && q[n - 1].side(q[0].intersection(q[1])) > EPS)
        q.pop_front(), n--;
    if (n < 3) return {};

    vector<P> ps(n);
    rep(i, n) ps[i] = q[i].intersection(q[(i + 1) % n]);
    return ps;
}

T area(const vector<P> &ps) {
    int N = ps.size();
    T a = 0;
    rep(i, N) a += (ps[i] - ps[0]) / (ps[(i + 1) % N] - ps[i]);
    return a / 2;
}

template <class OP>
void sweep_l(vector<P> &ps, OP op) {
    int N = ps.size();
    sort(ps.begin(), ps.end(), [](P a, P b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    vector<pair<int, int>> ss;
    rep(i, N) rep(j, N) if (i != j) ss.push_back({i, j});
    stable_sort(ss.begin(), ss.end(), [&](auto a, auto b) {
        return (ps[a.second] - ps[a.first]).angle_lt(ps[b.second] - ps[b.first]);
    });
    vector<int> p(N);
    rep(i, N) p[i] = i;
    for (auto [i, j] : ss) {
        op(p[i], p[j], N - p[i]);
        swap(ps[p[i]], ps[p[j]]);
        swap(p[i], p[j]);
    }
}

template <class OP>
void sweep_p(vector<P> &ps, OP op) {
    int N = ps.size();
    vector<pair<int, int>> events(2 * N - 2);
    rep(i, N) {
        rep(j, N - 1) events[j] = {j + (j >= i), 1};
        rep(j, N - 1) events[N - 1 + j] = {j + (j >= i), -1};
        P p = ps[i];
        sort(events.begin(), events.end(), [&](auto a, auto b) {
            P ap = (ps[a.first] - p) * a.second, bp = (ps[b.first] - p) * b.second;
            if (ap.half() != bp.half() || abs(ap / bp) > EPS) return bp.angle_lt(ap);
            return a.second > b.second;
        });
        int lt = 0;
        for (auto [j, d] : events)
            if (j != i && (d > 0 || (ps[j] - p).half())) lt += d;
        for (auto [j, d] : events) {
            if (j == i) continue;
            lt += d;
            if (d > 0) op(i, j, lt + 1);
        }
    }
}

ll N, M;
vector<P> ps;
double ans;

vector<P> cut_square_p(L l) {
    vector<P> poly;
    poly.push_back(P(0, 0));
    poly.push_back(P(M, 0));
    poly.push_back(P(M, M));
    poly.push_back(P(0, M));

    vector<L> H;
    rep(i, 4) {
        H.push_back(L(poly[i], poly[(i + 1) % 4] - poly[i]));
    }

    rep(i, 4) {
        if (H[i].parallel(l)) continue;
        P p = H[i].intersection(l);
        poly.push_back(p);
    }

    invrep(i, poly.size()) {
        bool out = l.side(poly[i]) > EPS;
        rep(k, 4) if (H[k].side(poly[i]) > EPS) out = true;
        if (out)
            poly.erase(poly.begin() + i);
    }

    sort(poly.begin(), poly.end(), [](P a, P b) {
        return (a - P(1, 1)).angle_lt(b - P(1, 1));
    });

    return poly;
}

vector<P> cut_square_h(L l) {
    vector<L> H;
    H.push_back(L(P(0, 0), P(M, 0)));
    H.push_back(L(P(M, 0), P(0, M)));
    H.push_back(L(P(M, M), P(-M, 0)));
    H.push_back(L(P(0, M), P(0, -M)));
    H.push_back(l);

    return halfplane_intersect(H);
}

void try_line(L l, int n) {
    cerr << "trying line at (" << l.o << ") with direction (" << l.d << ") with " << n << " points to the left" << endl;

    vector<P> poly = cut_square_p(l);
    cerr << "  polygon:";
    for (P p : poly) cerr << " (" << p << ")";
    cerr << endl;

    cerr << "  area: " << area(poly) << endl;
    double a = (double)n / N - area(poly) / (M * M);

    cerr << "  ans for this line: " << a << endl;
    ans = max(ans, a);

    assert(n <= N);
}

int find_left(L l) {
    int n = 0;
    for (P p : ps) {
        n += l.side(p) <= EPS;
    }
    return n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> M >> N;
    ps.resize(N);
    rep(i, N) cin >> ps[i];

    sweep_p(ps, [&](int i, int j, int n) {
        try_line(L(ps[i], ps[j] - ps[i]), n);
    });

    P corners[4] = {P(0, 0), P(M, 0), P(M, M), P(0, M)};
    rep(i, N) {
        rep(k, 4) {
            L l = L(corners[k], ps[i] - corners[k]);
            try_line(l, find_left(l));
            l.d = -l.d;
            try_line(l, find_left(l));
        }
        rep(k, 4) {
            P d = ps[i] - corners[k];
            swap(d.x, d.y);
            L l = L(ps[i], d.rot());
            try_line(l, find_left(l));
        }
    }

    cout << fixed << setw(10) << setprecision(10) << ans << endl;
}
