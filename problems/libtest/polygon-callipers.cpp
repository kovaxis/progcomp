// https://open.kattis.com/problems/roberthood

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

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
    T operator%(P r) const { return rot() * r; }
    T left(P a, P b) { return (b - a) % (*this - a); }

    T magsq() const { return x * x + y * y; }
    T mag() const { return sqrt(magsq()); }
    P unit() const { return *this / mag(); }

    bool half() const { return abs(y) <= EPS && x < -EPS || y < -EPS; }
    T angcmp(P r) const { // like strcmp(this, r), returns 0 if equal, - if this < r, + if this > r
        int h = (int)half() - r.half();
        return h ? h : r % *this;
    }
    T angcmp_rel(P a, P b) { // like strcmp(a, b), returns 0 if equal, - if a < b, + if a > b
        P z = *this;         // uses this as the cutting  point
        int h = z % a <= 0 && z * a < 0 || z % a < 0;
        h -= z % b <= 0 && z * b < 0 || z % b < 0;
        return h ? h : b % a;
    }

    bool operator==(P r) const { return abs(x - r.x) <= EPS && abs(y - r.y) <= EPS; }

    double angle() const { return atan2(y, x); }
    static P from_angle(double a) { return {cos(a), sin(a)}; }
};

// ccw order, excludes collinear points by default
vector<P> chull(vector<P> p) {
    if (p.size() < 3) return p;
    vector<P> r;
    int k = 0;
    sort(p.begin(), p.end(), [](P a, P b) { return a.x != b.x ? a.x < b.x : a.y < b.y; });
    for (P q : p) { // lower hull
        while (k >= 2 && r[k - 1].left(r[k - 2], q) >= 0)
            r.pop_back(), k--; // >= to > to add collinears
        r.push_back(q), k++;
    }
    r.pop_back(), k--;
    int m = k;
    for (int i = p.size() - 1; i >= 0; --i) { // upper hull
        while (k >= m + 2 && r[k - 1].left(r[k - 2], p[i]) >= 0)
            r.pop_back(), k--; // >= to > to add collinears
        r.push_back(p[i]), k++;
    }
    r.pop_back();
    return r;
}

// square dist of most distant points of a ccw convex polygon with NO COLLINEAR POINTS
T callipers(const vector<P> &p) {
    int n = p.size();
    T r = 0;
    for (int i = 0, j = n < 2 ? 0 : 1; i < j; i++) {
        for (;; j = (j + 1) % n) {
            r = max(r, (p[i] - p[j]).magsq());
            if ((p[(i + 1) % n] - p[i]) % (p[(j + 1) % n] - p[j]) <= EPS) break;
        }
    }
    return r;
}

int N;
vector<P> A;

int main() {
    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i];
    cout << fixed << setprecision(12) << sqrt(callipers(chull(A))) << endl;
}
