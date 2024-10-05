#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int INF = 1e9;

typedef int T;
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
};

struct Box {
    int i0, i1, j0, j1;
};

int N, M, S, K;
vector<vector<bool>> mp;
vector<Box> sec;

bool visit(int i, int j, Box &b) {
    if (i < 0 || j < 0 || i > 2 * N || j > 2 * M) return false;
    if (mp[i][j]) return false;
    mp[i][j] = true;
    b.i0 = min(b.i0, i);
    b.j0 = min(b.j0, j);
    b.i1 = max(b.i1, i);
    b.j1 = max(b.j1, j);
    visit(i - 1, j, b);
    visit(i + 1, j, b);
    visit(i, j - 1, b);
    visit(i, j + 1, b);
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> S >> K;
    mp.assign(N * 2 + 1, vector<bool>(M * 2 + 1));
    rep(k, K) {
        P s, t;
        cin >> s >> t;
        s = s * 2;
        t = t * 2;
        repx(i, min(s.x, t.x), max(s.x, t.x) + 1) {
            repx(j, min(s.y, t.y), max(s.y, t.y) + 1) {
                mp[i][j] = true;
            }
        }
    }

    rep(i, 2 * N + 1) mp[i][0] = true;
    rep(i, 2 * N + 1) mp[i][2 * M] = true;
    rep(j, 2 * M + 1) mp[0][j] = true;
    rep(j, 2 * M + 1) mp[2 * N][j] = true;
    rep(i, 2 * N + 1) rep(j, 2 * M + 1) {
        Box b{INF, -INF, INF, -INF};
        if (visit(i, j, b)) {
            b.i0 /= 2;
            b.i1 /= 2;
            b.j0 /= 2;
            b.j1 /= 2;
            b.i1 += 1;
            b.j1 += 1;
            sec.push_back(b);
        }
    }
    K = sec.size();

    pair<int, int> ans = {0, 0};
    // NOTE: maybe dice can fall partly outside the board
    // NOTE: dice may fall unaligned with the board? (probably not)
    rep(i0, N - S + 1) rep(j0, M - S + 1) {
        int i1 = i0 + S, j1 = j0 + S;
        pair<int, int> res{0, 0};
        for (Box b : sec) {
            if (i0 <= b.i0 && i1 >= b.i1 && j0 <= b.j0 && j1 >= b.j1) {
                res.first += 1;
                res.second += (b.i1 - b.i0) * (b.j1 - b.j0);
            }
        }
        ans = max(ans, res);
    }

    cout << ans.first << " " << ans.second << endl;
}
