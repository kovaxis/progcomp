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
    T left(P a, P b) const { return (b - a) / (*this - a); }

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

T in_convex(const vector<P> &p, P q) {
    int l = 1, h = p.size() - 2;
    assert(p.size() >= 3);
    while (l != h) { // collinear points are unsupported!
        int m = (l + h + 1) / 2;
        if (q.left(p[0], p[m]) >= 0) l = m;
        else h = m - 1;
    }
    T in = min(q.left(p[0], p[1]), q.left(p.back(), p[0]));
    return min(in, q.left(p[l], p[l + 1]));
}

int N, M, K;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;
    vector<P> ps(N);
    rep(i, N) cin >> ps[i];
    ll hit = 0;
    rep(j, M) {
        P p;
        cin >> p;
        ll h = in_convex(ps, p);
        hit += h >= 0;
        cerr << "rocket " << p << " hit " << h << endl;
    }
    cout << (hit >= K ? "YES\n" : "NO\n");
}
