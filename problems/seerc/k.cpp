#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

const ll INF = 1e18;

int N, M, Q;
vector<vector<pair<ll, int>>> G;

struct Range {
    int l, r, m, n;
    vector<ll> D[10];
};

map<pair<int, int>, Range> precomp;

vector<ll> dijkstra(int l, int r, int src) {
    vector<ll> D(r - l, INF);
    priority_queue<pair<ll, int>> q;
    D[src - l] = 0, q.push({0, src});
    while (!q.empty()) {
        auto [d, u] = q.top();
        d = -d, q.pop();
        if (d > D[u - l]) continue;
        for (auto [w, v] : G[u]) {
            if (v < l || v >= r) continue;
            if (d + w >= D[v - l]) continue;
            D[v - l] = d + w;
            q.push({-(d + w), v});
        }
    }
    return D;
}

void precompute(int l, int r) {
    int m = l + max(0, r - l - 10) / 2;
    int n = min(10, r - m);
    Range a = {l, r, m, n};
    rep(i, n) a.D[i] = dijkstra(l, r, m + i);
    precomp[{l, r}] = a;
    cerr << "built range [" << l + 1 << ", " << r << "] with middle [" << m + 1 << ", " << m + n << "]" << endl;
    if (m - l > 0) precompute(l, m);
    if (r - (m + n) > 0) precompute(m + n, r);
}

// a < b
// a & b must be inside [x.l, x.r]
ll getdist(int a, int b, Range &x) {
    cerr << "  querying range [" << x.l + 1 << ", " << x.r << "]" << endl;
    assert(x.l <= a && b < x.r);
    if (x.m <= a && a < x.m + x.n) {
        ll d = x.D[a - x.m][b - x.l];
        cerr << "    a is in middle: " << d << endl;
        return d;
    }
    if (x.m <= b && b < x.m + x.n) {
        ll d = x.D[b - x.m][a - x.l];
        cerr << "    b is in middle: " << d << endl;
        return d;
    }
    // across the middle
    cerr << "    across the middle" << endl;
    ll sol = INF;
    rep(k, x.n) {
        ll d = x.D[k][a - x.l] + x.D[k][b - x.l];
        cerr << "      across " << x.m + k + 1 << ": " << d << endl;
        sol = min(sol, d);
    }
    // to one side
    ll d = INF;
    if (b < x.m) {
        // both to the left
        cerr << "    to the left" << endl;
        d = getdist(a, b, precomp[{x.l, x.m}]);
    } else if (a >= x.m + x.n) {
        // both to the right
        cerr << "    to the right" << endl;
        d = getdist(a, b, precomp[{x.m + x.n, x.r}]);
    }
    sol = min(sol, d);
    return sol;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> Q;
    G.resize(N);
    rep(j, M) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--, v--;
        G[u].push_back({w, v});
        G[v].push_back({w, u});
    }

    precompute(0, N);

    rep(q, Q) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (a > b) swap(a, b);
        cerr << "querying distance between " << a + 1 << " and " << b + 1 << endl;
        ll d = getdist(a, b, precomp[{0, N}]);
        cerr << "  final distance is " << d << endl;
        if (d >= INF) {
            cout << "-1\n";
        } else {
            cout << d << "\n";
        }
    }
}