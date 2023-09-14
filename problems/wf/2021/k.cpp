#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

#define cerr \
    if (0) cerr

struct P {
    ll x, y;

    P operator+(P r) const { return {x + r.x, y + r.y}; }
    P operator-(P r) const { return {x - r.x, y - r.y}; }
    P operator-() const { return {-x, -y}; }

    ll magsq() { return x * x + y * y; }

    P perp() const { return {-y, x}; }
    ll operator*(P r) const { return x * r.x + y * r.y; }

    bool half() const { return y < 0 || (y == 0 && x < 0); }
    bool operator<(P r) const {
        if (half() != r.half()) return half() < r.half();
        return perp() * r > 0;
    }
    bool operator==(P r) const {
        return x == r.x && y == r.y;
    }
};

struct Poly {
    vector<P> A;

    int n() { return A.size(); }

    P &operator[](int i) { return A[(i % n() + n()) % n()]; }
};

int N;
vector<vector<int>> G;
vector<P> leaf;

Poly minkowski(vector<Poly> B) {
    // place bottom-left of polygons first
    rep(i, B.size()) {
        int k = 0;
        repx(j, 1, B[i].n()) {
            if (make_pair(B[i][j].y, B[i][j].x) < make_pair(B[i][k].y, B[i][k].x)) k = j;
        }
        rotate(B[i].A.begin(), B[i].A.begin() + k, B[i].A.end());
    }

    cerr << "computing minkowski sum of:" << endl;
    rep(i, B.size()) {
        cerr << "    ";
        for (P p : B[i].A) cerr << p.x << " " << p.y << ", ";
        cerr << endl;
    }

    P base = {0, 0};
    invrep(i, (int)B.size()) {
        base = base + B[i][0];
        if (B[i].n() == 1) {
            swap(B[i], B.back());
            B.pop_back();
        }
        assert(B[i].n() != 0);
    }
    // if B was originally empty should we return (0, 0)?
    if (B.empty()) return {{base}};
    priority_queue<pair<P, pair<int, int>>, vector<pair<P, pair<int, int>>>, greater<pair<P, pair<int, int>>>> q;
    rep(i, (int)B.size()) {
        q.push({B[i][1] - B[i][0], {i, 1}});
    }
    Poly out;
    while (!q.empty()) {
        auto [dir, ij] = q.top();
        auto [i, j] = ij;
        q.pop();
        out.A.push_back(base);
        base = base + dir;
        if (j < B[i].n()) {
            q.push({B[i][j + 1] - B[i][j], {i, j + 1}});
        }
    }

    cerr << "resulting sum: " << endl;
    for (P p : out.A) cerr << p.x << " " << p.y << ", ";
    cerr << endl;

    return out;
}

Poly convex_hull(vector<P> &ps) {
    int N = ps.size(), n = 0, k = 0;
    if (N <= 2) return {ps};
    sort(ps.begin(), ps.end(), [](P a, P b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    sort(++ps.begin(), ps.end(), [&](P l, P r) {
        ll x = (r - l).perp() * (ps[0] - l), d = (r - l) * (ps[0] - l);
        return x > 0 || x == 0 && d < 0;
    });

    vector<P> H;
    for (P p : ps) {
        while (n >= 2 && (H[n - 1] - p).perp() * (H[n - 2] - p) >= 0) H.pop_back(), n--;
        H.push_back(p), n++;
    }
    return {H};
}

Poly dfs(int u) {
    Poly out;

    if (G[u].empty()) out = {{leaf[u]}};
    else {
        vector<Poly> B;
        for (int v : G[u]) B.push_back(dfs(v));
        if (B.size() == 1) out = B[0];
        else {
            for (Poly &ps : B) {
                for (P &p : ps.A) p = -p;
            }

            rep(i, B.size()) if (B[i].n() > B.back().n()) swap(B[i], B.back());
            Poly large;
            swap(large, B.back());
            B.pop_back();

            vector<P> smallcands;
            rep(i, B.size()) {
                vector<Poly> B2 = B;
                for (P &p : B2[i].A) p = -p;
                Poly sm = minkowski(B2);
                smallcands.insert(smallcands.end(), sm.A.begin(), sm.A.end());
            }
            Poly smallhull = minkowski({large, convex_hull(smallcands)});

            for (P &p : large.A) p = -p;
            B.push_back(large);
            Poly largehull = minkowski(B);

            largehull.A.insert(largehull.A.end(), smallhull.A.begin(), smallhull.A.end());
            out = convex_hull(largehull.A);
        }
    }

    cerr << "polygon for " << u + 1 << ":" << endl;
    for (P p : out.A) {
        cerr << "    " << p.x << " " << p.y << endl;
    }

    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    G.resize(N), leaf.resize(N);
    rep(u, N) {
        int k;
        cin >> k;
        if (k == 0) {
            cin >> leaf[u].x >> leaf[u].y;
        } else {
            G[u].resize(k);
            rep(i, k) {
                cin >> G[u][i];
                G[u][i]--;
            }
        }
    }

    Poly cand = dfs(0);
    ll ans = 0;
    for (P p : cand.A) {
        ans = max(ans, p.magsq());
    }
    cout << ans << endl;
}
