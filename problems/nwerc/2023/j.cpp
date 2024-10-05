#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

const double PI = acos(-1);

struct P {
    double x, y;

    P operator-(P r) const { return {x - r.x, y - r.y}; }

    P rot(double ang) {
        return {-sin(ang) * y + cos(ang) * x, sin(ang) * x + cos(ang) * y};
    }
    double manh() const { return abs(x) + abs(y); }

    double mag() const { return sqrt(x*x + y*y); }
};

int N;
vector<P> A;

double dist(double ang, int u, int v) {
    return (A[v] - A[u]).rot(-ang).manh();
}

double solve(double ang) {
    vector<vector<double>> dp(N, vector<double>(1 << N));
    rep(u, N) dp[u][0] = 0;
    repx(m, 1, 1 << N) {
        rep(u, N) if (!((m >> u) & 1)) {
            double res = 1e100;
            rep(v, N) if ((m >> v) & 1) {
                int m2 = m & ~(1 << v);
                double d = dp[v][m2] + dist(ang, u, v);
                res = min(res, d);
            }
            dp[u][m] = res;
        }
    }

    double ans = 1e100;
    rep(u, N) {
        int m = (1 << N) - 1;
        m &= ~(1 << u);
        ans = min(ans, dp[u][m]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i].x >> A[i].y;

    double ans = 1e100;
    rep(i, N) repx(j, i+1, N) {
        P d = A[i] - A[j];
        double ang = atan2(d.y, d.x);
        ang = fmod(2*PI + ang, PI / 2);
        ans = min(ans, solve(ang));
    }

    cout << fixed << setprecision(12) << ans << endl;
}
