// https://open.kattis.com/problems/pointinpolygon

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

// get the area of a simple polygon in ccw order
// returns negative area for cw polygons
T area(const vector<P> &ps) {
    int N = ps.size();
    T a = 0;
    rep(i, N) a += (ps[i] - ps[0]) % (ps[(i + 1) % N] - ps[i]);
    return a;
}

// checks whether a point is inside a simple polygon
// returns 1 if inside, 0 if on border, -1 if outside
// O(N)
int in_poly(const vector<P> &p, P q) {
    int w = 0;
    rep(i, p.size()) {
        P a = p[i], b = p[(i + 1) % p.size()];
        T k = (b - a) % (q - a);
        T u = a.y - q.y, v = b.y - q.y;
        if (k > 0 && u < 0 && v >= 0) w++;
        if (k < 0 && v < 0 && u >= 0) w--;
        if (k == 0 && (q - a) * (q - b) <= 0) return 0;
    }
    return w ? 1 : -1;
}

int N, M;
vector<P> A, B;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    while (1) {
        cin >> N;
        if (N == 0) break;
        A.resize(N);
        rep(i, N) cin >> A[i];
        cin >> M;
        B.resize(M);
        rep(j, M) cin >> B[j];

        if (area(A) < 0) reverse(A.begin(), A.end());

        rep(j, M) {
            int z = in_poly(A, B[j]);
            if (z < 0) cout << "out\n";
            if (z > 0) cout << "in\n";
            if (z == 0) cout << "on\n";
        }
    }
}