#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (ll i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (ll i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

struct P {
    ll x, y;

    P(ll x, ll y) : x(x), y(y) {}
    P() : x(0), y(0) {}

    P operator+(P r) const { return {x + r.x, y + r.y}; }
    P operator-(P r) const { return {x - r.x, y - r.y}; }

    P rot() const { return {-y, x}; }

    ll operator*(P r) const { return x * r.x + y * r.y; }
    ll operator/(P r) const { return rot() * r; }
};

vector<P> convex_hull(vector<P> &ps) {
    int N = ps.size(), n = 0, k = 0;
    if (N <= 2) return ps;
    rep(i, N) if (make_pair(ps[i].y, ps[i].x) < make_pair(ps[k].y, ps[k].x)) k = i;
    swap(ps[k], ps[0]);
    sort(++ps.begin(), ps.end(), [&](P l, P r) {
        ll x = (r - l) / (ps[0] - l), d = (r - l) * (ps[0] - l);
        return x > 0 || x == 0 & d < 0;
    });
    vector<P> H;
    for (P p : ps) {
        while (n >= 2 && (H[n - 1] - p) / (H[n - 2] - p) >= 0) H.pop_back(), n--;
        H.push_back(p), n++;
    }
    return H;
}

const ll INF = 2e9;

struct R {
    ll n, d;

    bool operator<(R r) const {
        // n1 / d1 < n2 / d2
        // n1 * d2 < n2 * d1
        return n * r.d < r.n * d;
    }

    bool operator==(R r) const { return n * r.d == r.n * d; }
    bool operator!=(R r) const { return n * r.d != r.n * d; }
    R operator-() const { return {-n, d}; }
};

int N;
vector<ll> X, V;
vector<int> nxt, prv, alive;
vector<R> T;
priority_queue<pair<R, int>> Q;

R ttc(int i, int j) {
    if (V[i] - V[j] <= 0) return {-1, 1};
    return {X[j] - X[i], V[i] - V[j]};
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    X.resize(N), V.resize(N);
    rep(i, N) cin >> X[i] >> V[i];

    T.resize(N - 1);
    rep(i, N - 1) {
        T[i] = ttc(i, i + 1);
        if (T[i].n > 0) Q.push({-T[i], i});
        cerr << "drones " << i + 1 << " and " << i + 2 << " crash at " << T[i].n << "/" << T[i].d << endl;
    }

    nxt.resize(N), prv.resize(N), alive.resize(N, true);
    rep(i, N) nxt[i] = i + 1, prv[i] = i - 1;

    while (!Q.empty()) {
        auto thispair = Q.top();
        R t = -thispair.first;
        int i = thispair.second;
        int j = nxt[i];
        Q.pop();
        cerr << "processing potential crash at " << t.n << "/" << t.d << endl;
        if (!alive[i] || t != T[i] || j >= N || !alive[j]) continue;

        // collision between i and j
        cerr << "crash between " << i + 1 << " and " << j + 1 << endl;
        alive[i] = false;
        alive[j] = false;
        int l = prv[i], r = nxt[j];
        if (l >= 0) nxt[l] = r;
        if (r < N) prv[r] = l;
        if (l >= 0 && r < N) {
            T[l] = ttc(l, r);
            if (T[l].n > 0) Q.push({-T[l], l});
        }
    }

    int m = 0;
    rep(i, N) m += alive[i];
    cout << m << endl;
    bool first = true;
    rep(i, N) if (alive[i]) {
        if (first) first = false;
        else cout << " ";
        cout << i + 1;
    }
    cout << endl;
}
