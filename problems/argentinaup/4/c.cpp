#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

typedef double T;
const T EPS = 1e-9;

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

    double angle() const { return atan2(y, x); }
    static P from_angle(double a) { return {cos(a), sin(a)}; }
};

// a segment or an infinite line
// does not handle point segments correctly!
struct L {
    P o, d;

    L() : o(), d() {}
    L(P o, P d) : o(o), d(d) {}

    // UNTESTED
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

    // check if segments intersect
    bool seg_collide(L r) const {
        T z = d / r.d;
        if (abs(z) <= EPS) {
            if (abs(side(r.o)) > EPS) return false;
            T s = (r.o - o) * d, e = s + r.d * d;
            if (s > e) swap(s, e);
            return s <= d * d + EPS && e >= -EPS;
        }
        T s = inter(r), t = -r.inter(*this);
        if (z < 0) s = -s, t = -t, z = -z;
        return s >= -EPS && s <= z + EPS && t >= -EPS && t <= z + EPS;
    }

    // full segment intersection
    // produces a point segment if the intersection is a point
    // however it **does not** handle point segments as input!
    bool seg_inter(L r, L *out) const {
        T z = d / r.d;
        if (abs(z) <= EPS) {
            if (abs(side(r.o)) > EPS) return false;
            if (r.d * d < 0) r = {r.o + r.d, -r.d};
            P s = o * d < r.o * d ? r.o : o;
            P e = (o + d) * d < (r.o + r.d) * d ? o + d : r.o + r.d;
            if (s * d > e * d) return false;
            return *out = L(s, e - s), true;
        }
        T s = inter(r), t = -r.inter(*this);
        if (z < 0) s = -s, t = -t, z = -z;
        if (s >= -EPS && s <= z + EPS && t >= -EPS && t <= z + EPS)
            return *out = L(o + d * s / z, P()), true;
        return false;
    }

    // check if the given point is on the segment
    bool point_on_seg(P r) const {
        if (abs(side(r)) > EPS) return false;
        if ((r - o) * d < -EPS) return false;
        if ((r - o - d) * d > EPS) return false;
        return true;
    }

    // get the point in this line that is closest to a given point
    P closest_to(P r) const {
        P dr = d.rot();
        return r + (o - r) * dr * dr / d.magsq();
    }
};

struct NodeId {
    // -1 if starting point
    int along;
    // N if infinity
    // -1 if starting point
    int across;
    // If infinity, `false` is forward and `true` is backward infinity
    bool backward;

    pair<pair<int, int>, bool> id() const { return make_pair(make_pair(along, across), backward); }
    bool operator<(NodeId r) const { return id() < r.id(); }
    bool operator==(NodeId r) const { return id() == r.id(); }
};

int N;
ll M;
P start;
vector<L> A;
vector<string> names;
map<NodeId, NodeId> nxt;

string streetname(int i) {
    if (i == -1) return "start";
    else if (i == N) return "infinity";
    else return names[i];
}
string nodename(NodeId id) {
    stringstream s;
    s << streetname(id.along) << "-" << streetname(id.across) << "-" << (id.backward ? "B" : "F");
    // s << "along " << streetname(id.along) << ", across " << streetname(id.across) << ", going " << (id.backward ? "backward" : "forward");
    return s.str();
}

int main() {
    cin >> N >> M >> start;
    A.resize(N), names.resize(N);
    rep(i, N) {
        P s, e;
        cin >> names[i] >> s >> e;
        if (e.x < s.x) swap(s, e);
        A[i] = L(s, e - s);
    }

    NodeId cur;
    rep(i, N) {
        vector<pair<double, int>> line;
        line.push_back({-INFINITY, N});
        line.push_back({INFINITY, N});
        rep(j, N) {
            if (A[i].d / A[j].d == 0) continue;
            line.push_back({A[i].inter(A[j]) / (A[i].d / A[j].d), j});
        }
        sort(line.begin(), line.end());
        cerr << "streets in order for " << streetname(i) << ":" << endl;
        for (auto [d, j] : line) cerr << "  [" << d << "] " << streetname(j) << endl;
        rep(k, line.size()) {
            auto [_d, j] = line[k];
            if (k == 0) nxt[{i, N, true}] = {i, N, true};
            else if (k == (int)line.size() - 1) nxt[{i, N, false}] = {i, N, false};
            else {
                bool right_is_fw = A[i].d / A[j].d > 0;
                nxt[{j, i, right_is_fw}] = {i, line[k - 1].second, true};
                nxt[{j, i, !right_is_fw}] = {i, line[k + 1].second, false};
            }
        }
        if ((start - A[i].o) / A[i].d == 0) {
            auto it = lower_bound(line.begin(), line.end(), make_pair((start - A[i].o) * A[i].d / A[i].d.magsq() - EPS, 0));
            cur = {i, (it == line.end() ? N : it->second), false};
        }
    }

    for (auto [k, v] : nxt) {
        cerr << "[" << nodename(k) << "] -> [" << nodename(v) << "]" << endl;
    }

    map<NodeId, ll> seen;
    ll cnt = 0;
    bool skipped = false;
    cerr << "starting " << nodename(cur) << endl;
    while (cnt < M) {
        if (!skipped && seen.count(cur)) {
            ll looplen = cnt - seen[cur];
            ll full_loops = (M - cnt) / looplen;
            cerr << "speedrunning " << full_loops << " full loops of length " << looplen << " to " << nodename(cur) << endl;
            cnt += full_loops * looplen;
            skipped = true;
        }
        if (cnt >= M) break;
        seen[cur] = cnt;
        cur = nxt[cur];
        cnt++;
        cerr << "moved to " << nodename(cur) << endl;
    }

    cout << names[cur.along] << endl;
}
