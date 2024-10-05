#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

ll ext_gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll d = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

ll W, H, K1, K0, M, N, A;
vector<pair<int, int>> rawbricks;

ll mod(ll x, ll m) { return (x % m + m) % m; }

// multiply two large numbers modulo M, where M can be of the order of 10^10.
ll mul(ll x, ll y) {
    ll ans = 0, y2 = y, x2 = x;
    while (y2) {
        if (y2 & 1) ans = (ans + x2) % M;
        x2 = (x2 << 1) % M;
        y2 >>= 1;
    }
    // cerr << x << " * " << y << " mod " << M << " = " << ans << endl;
    return ans;
}

using Brick = pair<ll, pair<int, pair<short, short>>>;

// alpha values for all bricks, for all 4 values of g
set<Brick> points[4];
vector<vector<pair<int, Brick>>> brickpoints;

int gamma(ll x, ll y) { return mod(y - x, 4); }

ll beta(ll x, ll y) {
    ll K1H = mul(K1, H);
    return mod(mul(K1H, x) - mul((K1H - 1 + M) % M, y), M);
}

void normalize(ll& x, ll& y, int vx, int vy) {
    x = mod(x * vx, 4 * W);
    y = mod(y * vy, 4 * H);
}

void addmirror(ll x, ll y, int i, int dx, int dy) {
    int g = mod(y - x, 4);
    ll alpha = (mul(mul(K1, H), mod(x - y, M)) + y) % M;
    Brick b = {alpha, {i, {dx, dy}}};
    points[g].insert(b);
    brickpoints[i].push_back({g, b});
}

void addpoint(ll x, ll y, int i, int dx, int dy) {
    addmirror(x, y, i, dx, dy);
    addmirror(4 * W - x, y, i, dx, dy);
    addmirror(x, 4 * H - y, i, dx, dy);
    addmirror(4 * W - x, 4 * H - y, i, dx, dy);
}

Brick firstcollision(ll x, ll y) {
    ll b = beta(x, y), g = gamma(x, y);
    auto it = points[g].lower_bound({b, {0, {-1, -1}}});
    if (it == points[g].end()) it = points[g].begin();
    Brick point = *it;
    point.first = mod(point.first - b, M);

    int i = point.second.first;
    for (auto& p : brickpoints[i]) points[p.first].erase(p.second);

    /*
    cerr << "starting from (" << (float)x / 2 << ", " << (float)y / 2
         << "), collided with block " << i + 1 << " at ("
         << (float)mod(x + point.first, 4 * W) / 2 << ", "
         << (float)mod(y + point.first, 4 * H) / 2 << ") after " <<
    point.first
         << " seconds" << endl;
    // */

    return point;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> W >> H >> N;
    rawbricks.resize(N), brickpoints.resize(N);
    rep(i, N) cin >> rawbricks[i].first >> rawbricks[i].second;

    M = 4 * W * H;
    ext_gcd(4 * H, 4 * W, K1, K0);
    K0 = (K0 % M + M) % M;
    K1 = (K1 % M + M) % M;

    cerr << "W = " << W << ", H = " << H << ", K1 = " << K1 << ", K0 = " << K0
         << endl;

    rep(i, N) {
        ll x = 2 * rawbricks[i].first, y = 2 * rawbricks[i].second;
        addpoint(x - 1, y, i, 1, -1);
        addpoint(x, y - 1, i, -1, 1);
        addpoint(x - 2, y - 1, i, -1, 1);
        addpoint(x - 1, y - 2, i, 1, -1);
    }

    ll time = 0;
    ll x = W, y = 0;
    normalize(x, y, -1, 1);
    rep(i, N) {
        Brick b = firstcollision(x, y);
        time += b.first;

        x = mod(x + b.first, 4 * W);
        y = mod(y + b.first, 4 * H);
        auto& v = b.second.second;
        normalize(x, y, v.first, v.second);
    }
    cout << time << endl;
}
