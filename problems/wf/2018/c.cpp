#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// typedef long long ll;

#define repx(i, a, b) for (int i = a; i < int(b); i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b; i-- > int(a);)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (1) cerr

struct Edge {
    int v, c;
};

struct ll {
    long long sml = 0, big = 0;

    ll(long long x) : sml(x) {}
    ll(long long x, long long y) : sml(x), big(y) {}

    ll operator+(ll r) const { return {sml + r.sml, big + r.big}; }
    ll operator-(ll r) const { return {sml - r.sml, big - r.big}; }
    ll operator-() const { return {-sml, -big}; }
    bool operator<(ll r) const {
        if (big != r.big) return big < r.big;
        return sml < r.sml;
    }
    bool operator>(ll r) const { return r < *this; }
};

struct Curve {
    priority_queue<ll, vector<ll>, greater<ll>> A;
    ll D = 0;

    bool empty() const { return A.empty(); }

    ll slope() const {
        return A.top() + D;
    }

    ll pop() {
        ll m = slope();
        A.pop();
        return m;
    }

    void push(ll m) {
        A.push(m - D);
    }

    void merge(Curve &other) {
        if (A.size() < other.A.size()) swap(*this, other);
        while (!other.empty()) {
            push(other.pop());
        }
        other.D = 0;
    }
};

struct CurvePair {
    ll Y = 0;
    Curve L, R;

    void merge(CurvePair &other) {
        L.merge(other.L);
        R.merge(other.R);
        Y = Y + other.Y;
        other.Y = 0;
    }
};

const ll INF = {0, 1};

int N;
vector<vector<Edge>> G;
vector<int> W;

CurvePair dfs(int u, int p, int c) {
    CurvePair me;
    if (W[u] > 0) {
        rep(i, W[u]) me.R.push(0);
    }
    if (W[u] < 0) {
        rep(i, -W[u]) {
            me.L.push(-INF);
            me.Y = me.Y + INF;
        }
    }
    for (Edge e : G[u])
        if (e.v != p) {
            CurvePair sub = dfs(e.v, u, e.c);
            me.merge(sub);
        }
    while (!me.L.empty() && !me.R.empty() && me.L.slope() + me.R.slope() < 0) {
        ll l = me.L.pop(), r = me.R.pop();
        me.Y = me.Y + r + l;
        me.L.push(-r);
        me.R.push(-l);
    }
    me.L.D = me.L.D + c;
    me.R.D = me.R.D + c;
    return me;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    G.resize(N);
    rep(j, N - 1) {
        int u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        G[u].push_back({v, c});
        G[v].push_back({u, c});
    }
    W.resize(N);
    rep(u, N) {
        int x, y;
        cin >> x >> y;
        W[u] = x - y;
    }

    ll ans = dfs(0, -1, 0).Y;

    cout << ans.sml << endl;
}
