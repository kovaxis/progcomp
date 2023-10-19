// http://codeforces.com/group/3qadGzUdR4/contest/101707/problem/H
// AC

// get the point of a convex polygon that is the farthest in a particular direction

#include <bits/stdc++.h>
#ifdef DEMETRIO
#define deb(...) fprintf(stderr, __VA_ARGS__)
#define deb1(x) cerr << #x << " = " << x << endl
#else
#define deb(...) 0
#define deb1(x) 0
#endif
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i, a, b) for (int i = a, ThxDem = b; i < ThxDem; ++i)
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;

#define double ll
#define EPS 0

struct pt { // for 3D add z coordinate
    double x, y;
    pt(double x, double y) : x(x), y(y) {}
    pt() {}
    double norm2() { return *this * *this; }
    double norm() { return sqrt(norm2()); }
    bool operator==(pt p) { return abs(x - p.x) < EPS && abs(y - p.y) < EPS; }
    pt operator+(pt p) const { return pt(x + p.x, y + p.y); }
    pt operator-(pt p) const { return pt(x - p.x, y - p.y); }
    pt operator*(double t) { return pt(x * t, y * t); }
    pt operator/(double t) { return pt(x / t, y / t); }
    double operator*(pt p) { return x * p.x + y * p.y; }
    //	pt operator^(pt p){ // only for 3D
    //		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
    double angle(pt p) { // redefine acos for values out of range
        return acos(*this * p / (norm() * p.norm()));
    }
    pt unit() { return *this / norm(); }
    double operator%(pt p) { return x * p.y - y * p.x; }
    // 2D from now on
    bool operator<(pt p) const { // for convex hull
        return x < p.x || x == p.x && y < p.y;
    }
    bool left(pt p, pt q) { // is it to the left of directed line pq?
        return (q - p) % (*this - p) >= 0;
    }
    pt rot(pt r) { return pt(*this % r, *this * r); }
    pt rot(double a) { return rot(pt(sin(a), cos(a))); }

    double angcmp_rel(pt a, pt b) { // like strcmp(a, b), returns 0 if equal, - if a < b, + if a > b
        pt z = *this;               // uses this as the cutting  point
        int h = z % a <= 0 && z * a < 0 || z % a < 0;
        h -= z % b <= 0 && z * b < 0 || z % b < 0;
        return h ? h : b % a;
    }
    pt perp() const { return {-y, x}; }
};
pt ccw90(1, 0);
pt cw90(-1, 0);

// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<pt> chull(vector<pt> p) {
    vector<pt> r;
    sort(p.begin(), p.end()); // first x, then y
    fore(i, 0, p.size()) {    // lower hull
        while (r.size() >= 2 && r.back().left(r[r.size() - 2], p[i])) r.pop_back();
        r.pb(p[i]);
    }
    r.pop_back();
    int k = r.size();
    for (int i = p.size() - 1; i >= 0; --i) { // upper hull
        while (r.size() >= k + 2 && r.back().left(r[r.size() - 2], p[i])) r.pop_back();
        r.pb(p[i]);
    }
    r.pop_back();
    return r;
}

int extremal(const vector<pt> &p, pt d) {
    // fore(i, 0, p.size()) cerr << "p[" << i << "] = " << p[i].x << " " << p[i].y << endl;

    int n = p.size(), l = 0, r = n - 1;
    while (l < r) {
        pt e0 = (p[n - 1] - p[0]).perp();
        int m = (l + r + 1) / 2;
        pt e = (p[(m + n - 1) % n] - p[m]).perp();
        if (e0.angcmp_rel(d, e) < 0) r = m - 1;
        else l = m;
    }
    // cerr << "extremal in direction " << d.x << " " << d.y << ": " << l << endl;
    return l;
}

int sgn(double x) { return x < -EPS ? -1 : x > EPS; }
struct pol {
    int n;
    vector<pt> p;
    pol() {}
    pol(vector<pt> _p) {
        p = _p;
        n = p.size();
    }
    void normalize() { // (call before haslog, remove collinear first)
        if (p[2].left(p[0], p[1])) reverse(p.begin(), p.end());
        int pi = min_element(p.begin(), p.end()) - p.begin();
        vector<pt> s(n);
        fore(i, 0, n) s[i] = p[(pi + i) % n];
        p.swap(s);
    }
    pt farthest(pt v) { // O(log(n)) only CONVEX
        return p[extremal(p, v)];
    }
};

ll a[100005], b[100005], c[100005];
int m, n;
vector<pt> v;
pol p;

bool doit(ll a, ll b, ll c) {
    pt v(a, b);
    return p.farthest(v) * v + c >= 0 && p.farthest(pt(0, 0) - v) * v + c <= 0;
}

int main() {
    scanf("%d%d", &m, &n);
    fore(i, 0, m) scanf("%lld%lld%lld", a + i, b + i, c + i);
    fore(i, 0, n) {
        ll x, y;
        scanf("%lld%lld", &x, &y);
        v.pb(pt(x, y));
    }
    auto q = chull(v);
    if (q.empty()) q = v;
    p = pol(q);
    vector<int> r;
    fore(i, 0, m) if (doit(a[i], b[i], c[i])) r.pb(i);
    printf("%d\n", SZ(r));
    fore(i, 0, SZ(r)) {
        if (i) putchar(' ');
        printf("%d", r[i] + 1);
    }
    puts("");
    return 0;
}