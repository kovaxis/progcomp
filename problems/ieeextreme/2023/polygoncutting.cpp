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

T area2(const vector<P> &p) {
    int n = p.size();
    T a = 0;
    rep(i, n) a += (p[(i + 1) % n] - p[i]) % (p[i] - p[0]);
    return a;
}

int N, M;
vector<P> A;
vector<pair<int, int>> evs;

int K;
vector<vector<int>> G;
vector<ll> C;

struct Block {
    int id;
    ll area;
    int end;
};

Block translate(int l) {
    cerr << "translating from " << evs[l].first << endl;
    int u = G.size();
    G.push_back({});
    C.push_back(0);
    ll missing_area = 0;
    repx(i, l + 1, (int)evs.size()) {
        repx(j, evs[i - 1].first, evs[i].first) {
            C[u] += (A[j + 1] - A[evs[l].first]) % (A[j] - A[evs[l].first]);
        }
        if (evs[i].second > 0) {
            cerr << "sub-block at " << evs[i].first << endl;
            Block sub = translate(i);
            C[u] += (A[evs[sub.end].first] - A[evs[l].first]) % (A[evs[i].first] - A[evs[l].first]);
            i = sub.end;
            G[u].push_back(sub.id);
            missing_area += sub.area;
        } else {
            cerr << "ends at " << evs[i].first << " with own area " << C[u] << " and full area " << C[u] + missing_area << endl;
            return {u, C[u] + missing_area, i};
        }
    }
    assert(false);
}

pair<ll, ll> dfs(int u) {
    ll best_blank = 0, best_color = C[u];
    for (int v : G[u]) {
        auto [sub_blank, sub_color] = dfs(v);
        best_blank += max(sub_blank, sub_color);
        best_color += sub_blank;
    }
    return {best_blank, best_color};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    A.resize(N);
    rep(i, N) cin >> A[i];
    rep(j, M) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u > v) swap(u, v);
        evs.push_back({u, 1});
        evs.push_back({v, -1});
        cerr << "parentheses from " << u << " to " << v << endl;
    }

    sort(evs.begin(), evs.end());

    int l = 0;
    G.push_back({});
    C.push_back(area2(A));
    cerr << "total area " << C[0] << endl;
    while (l < evs.size()) {
        Block b = translate(l);
        l = b.end + 1;
        C[0] -= b.area;
        G[0].push_back(b.id);
    }

    auto [blank, color] = dfs(0);
    ll ans = max(blank, color);
    cout << ans << endl;
}
