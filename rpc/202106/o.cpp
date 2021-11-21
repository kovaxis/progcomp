#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

typedef long long ll;

struct Fpiece {
    ll up_to;
    ll y;
};

struct Gpiece {
    ll up_to;
    ll a;
    ll b;
    ll c;
};

int n;
Fpiece fdesc[501];

int m;
Gpiece gdesc[501];

pair<double, double> find_zeros(double a, double b, double c) {
    if (a == 0.) {
        if (b == 0.) return {-1, -1};
        double x = -c / b;
        return {x, x};
    }
    double d = b * b - 4 * a * c;
    if (d < 0) return {-1, -1};
    d = sqrt(d);
    return {(-b + d) / (2. * a), (-b - d) / (2. * a)};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    rep(i, n) {
        auto& f = fdesc[i];
        cin >> f.up_to >> f.y;
    }
    cin >> m;
    rep(i, m) {
        auto& g = gdesc[i];
        cin >> g.up_to >> g.a >> g.b >> g.c;
    }
    gdesc[m] = gdesc[m - 1];
    m += 1;

    int fi = 0, gi = 0;
    double cur = 0.;
    double area = 0.;
    while (fi < n - 1 || gi < m - 1) {
        auto& f = fdesc[fi];
        auto& g = gdesc[gi];
        ll nextf = fdesc[fi].up_to;
        ll nextg = gdesc[gi].up_to;
        double up_to;
        if (nextf < nextg) {
            // advance f
            up_to = (double)nextf;
            fi += 1;
        } else {
            // advance g
            up_to = (double)nextg;
            gi += 1;
        }
        auto inters = find_zeros(g.a, g.b, g.c - f.y);
        double a = (double)g.a / 3.;
        double b = (double)g.b / 2.;
        double c = (double)(g.c - f.y);
        double segs[4] = {cur, min(inters.first, inters.second),
                          max(inters.first, inters.second), up_to};
        rep(i, 1, 4) {
            segs[i] = max(min(segs[i], up_to), cur);
            double x2 = segs[i];
            double x1 = segs[i - 1];
            area += abs(a * (x2 * x2 * x2 - x1 * x1 * x1) +
                        b * (x2 * x2 - x1 * x1) + c * (x2 - x1));
        }
        cur = up_to;
    }
    cout << fixed << setw(7) << setprecision(7) << area << endl;
}
