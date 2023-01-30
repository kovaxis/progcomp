// https://codeforces.com/problemsets/acmsguru/problem/99999/253

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

typedef ll T;
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

struct InConvex {
    vector<P> ps;
    T ll, lh, rl, rh;
    int N, m;

    InConvex() {}
    InConvex(const vector<P> &p) : ps(p), N(ps.size()), m(0) {
        assert(N >= 2);
        rep(i, N) if (ps[i].x < ps[m].x) m = i;
        rotate(ps.begin(), ps.begin() + m, ps.end());
        rep(i, N) if (ps[i].x > ps[m].x) m = i;
        ll = lh = ps[0].y, rl = rh = ps[m].y;
        for (P p : ps) {
            if (p.x == ps[0].x) ll = min(ll, p.y), lh = max(lh, p.y);
            if (p.x == ps[m].x) rl = min(rl, p.y), rh = max(rh, p.y);
        }
    }

    int in_poly(P p) {
        if (p.x < ps[0].x || p.x > ps[m].x) return 1;
        if (p.x == ps[0].x) return p.y < ll || p.y > lh;
        if (p.x == ps[m].x) return p.y < rl || p.y > rh;
        int r = upper_bound(ps.begin(), ps.begin() + m, p, [](P a, P b) { return a.x < b.x; }) - ps.begin();
        T z = (ps[r - 1] - ps[r]) / (p - ps[r]);
        if (z >= 0) return !!z;
        r = upper_bound(ps.begin() + m, ps.end(), p, [](P a, P b) { return a.x > b.x; }) - ps.begin();
        z = (ps[r - 1] - ps[r % N]) / (p - ps[r % N]);
        if (z >= 0) return !!z;
        return -1;
    }
};

int N, M, K;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;
    vector<P> ps(N);
    rep(i, N) cin >> ps[i];
    InConvex conv(ps);
    ll hit = 0;
    rep(j, M) {
        P p;
        cin >> p;
        int h = conv.in_poly(p);
        hit += h <= 0;
        cerr << "rocket " << p << " hit " << h << endl;
    }
    cout << (hit >= K ? "YES\n" : "NO\n");
}
