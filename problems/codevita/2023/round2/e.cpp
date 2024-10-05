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

int N, M, K;
vector<vector<bool>> mp;
int inside, outside;

bool visit(int i, int j) {
    if (i < 0 || j < 0 || i > 2 * N || j > 2 * M) return false;
    if (mp[i][j]) return false;
    mp[i][j] = true;
    visit(i - 1, j);
    visit(i + 1, j);
    visit(i, j - 1);
    visit(i, j + 1);
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;
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

    rep(i, 2 * N + 1) outside += visit(i, 0);
    rep(i, 2 * N + 1) outside += visit(i, 2 * M);
    rep(j, 2 * M + 1) outside += visit(0, j);
    rep(j, 2 * M + 1) outside += visit(2 * N, j);
    rep(i, 2 * N + 1) rep(j, 2 * M + 1) inside += visit(i, j);

    int ans = round(100 * double(outside) / double(inside + outside));
    cout << ans << endl;
}
