#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct P {
    double x, y;

    P operator+(P r) { return {x + r.x, y + r.y}; }
    P operator-(P r) { return {x - r.x, y - r.y}; }
    P operator*(double r) { return {x * r, y * r}; }
    friend P operator*(double r, P s) { return {s.x * r, s.y * r}; }
    P operator/(double r) { return {x / r, y / r}; }

    double operator*(P r) { return x * r.x + y * r.y; }

    P perp() { return {-y, x}; }

    double magsq() { return x * x + y * y; }
    double mag() { return sqrt(magsq()); }

    friend istream &operator>>(istream &s, P &p) {
        return s >> p.x >> p.y;
    }
    friend ostream &operator<<(ostream &s, P p) {
        return s << p.x << " " << p.y;
    }
};

struct L {
    P o, d;

    P closest_to(P r) {
        P dr = d.perp();
        return r + (o - r) * dr * dr / d.magsq();
    }
};

struct F {
    L l;
    double z0, z1;
};

const double PI = acos(-1);

int N, M;
vector<vector<P>> A;
vector<F> B;

bool can_watch(double theta) {
    double tant = tan(theta / 180 * PI);
    rep(i, N) {
        bool cansee = false;
        rep(j, M) {
            L l = B[j].l;
            bool seeall = true;
            for (P p : A[i]) {
                double s = (p - l.o) * l.d / l.d.magsq();
                if (s < 0 || s > 1) {
                    seeall = false;
                }
                double z = B[j].z0 + (B[j].z1 - B[j].z0) * s;
                double maxd = tant * z;
                double d2 = (p - (l.o + l.d * s)).magsq();
                if (d2 > maxd * maxd) {
                    seeall = false;
                }
            }
            if (seeall) cansee = true;
        }
        if (!cansee) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    A.resize(N);
    rep(i, N) {
        int K;
        cin >> K;
        A[i].resize(K);
        rep(k, K) cin >> A[i][k];
    }
    B.resize(M);
    rep(j, M) {
        P p0, p1;
        cin >> p0 >> B[j].z0 >> p1 >> B[j].z1;
        B[j].l = {p0, p1 - p0};
    }

    double l = 0, r = 90;
    rep(iter, 40) {
        double m = (l + r) / 2;
        if (can_watch(m)) r = m;
        else l = m;
    }
    double ans = (l + r) / 2;

    if (ans > 90 - 1e-9) cout << "impossible" << endl;
    else cout << fixed << setprecision(9) << ans << endl;
}
