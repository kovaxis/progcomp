#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const double PI = 3.14;

typedef double T;
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
    T mag() const { return T(ceil(sqrt(magsq()))); }
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
    static P from_angle(double a) { return {T(cos(a)), T(sin(a))}; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    P A, B, C;
    cin >> A >> B >> C;
    B = B - A;
    C = C - A;

    ll target = ceil(PI * B.mag() * B.mag());
    ll fence = ceil(PI * C.mag() * C.mag());
    if (fence < target) {
        // shiva pays krishna money for missing amount
        cout << "Krishna " << (target - fence) * 20 << endl;
    } else if (fence > target) {
        // krishna gives back land as close as the deserved amount
        ll deserve = fence - target;
        ll best = 0;
        rep(a, 10000) {
            ll area = (ll)a * a;
            if (abs(area - deserve) <= abs(best - deserve)) best = area;
        }

        fence -= best;

        // differences are settled in money
        if (fence < target) {
            // still missing some, shiva pays in money
            cout << "Krishna " << (target - fence) * 20 << endl;
        } else if (fence > target) {
            // krishna took too much, give back money
            cout << "Shiva " << (fence - target) * 20 << endl;
        } else {
            // perfect
            cout << "-1" << endl;
        }
    } else {
        // perfect match
        cout << "-1" << endl;
    }
}
