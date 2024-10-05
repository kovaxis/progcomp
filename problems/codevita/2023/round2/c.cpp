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

int N, M;
vector<vector<bool>> mp;
vector<vector<int>> D;
P src, dst, mv;
vector<P> que;

void check(P s, P t) {
    if (t.x < 0 || t.y < 0 || t.x >= N || t.y >= M) return;
    if (mp[t.x][t.y]) return;
    if (D[t.x][t.y] <= D[s.x][s.y] + 1) return;
    D[t.x][t.y] = D[s.x][s.y] + 1;
    que.push_back(t);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    mp.assign(N, vector<bool>(M));
    rep(i, N) rep(j, M) {
        int x;
        cin >> x;
        mp[i][j] = x;
    }
    cin >> src >> dst >> mv;

    D.assign(N, vector<int>(M, INF));
    D[src.x][src.y] = 0;
    int q = 0;
    que.push_back(src);
    while (q < (int)que.size()) {
        P p = que[q++];
        check(p, p + mv);
        check(p, p - mv);
        check(p, p + mv.rot());
        check(p, p - mv.rot());
    }

    // NOTE: what about "can't reach"
    cout << D[dst.x][dst.y] << endl;
}
