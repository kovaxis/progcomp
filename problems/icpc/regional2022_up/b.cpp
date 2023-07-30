#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll INF = LLONG_MAX;

struct Line {
    mutable ll a, b, c;

    bool operator<(Line r) const { return a < r.a; }
    bool operator<(ll x) const { return c < x; }
};

// dynamically insert `a*x + b` lines and query for maximum at any x
// all operations have complexity O(log N)
// UNTESTED
struct LineContainer : multiset<Line, less<>> {

    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }

    bool isect(iterator x, iterator y) {
        if (y == end()) return x->c = INF, 0;
        if (x->a == y->a) x->c = x->b > y->b ? INF : -INF;
        else x->c = div(y->b - x->b, x->a - y->a);
        return x->c >= y->c;
    }

    void add(ll a, ll b) {
        // a *= -1, b *= -1 // for min
        auto z = insert({a, b, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->c >= y->c) isect(x, erase(y));
    }

    ll query(ll x) {
        if (empty()) return -INF; // INF for min
        auto l = *lower_bound(x);
        return l.a * x + l.b;
        // return -l.a * x - l.b; // for min
    }
};

struct St {
    vector<LineContainer> a;

    St() {}
    St(int N) : a(4 * N) {} // node neutral

    // query for range [l, r)
    ll query(ll x, int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (l <= vl && r >= vr) return a[v].query(x); // item construction
        int vm = (vl + vr) / 2;
        if (l >= vr || r <= vl) return -INF;                                          // item neutral
        return max(query(x, l, r, 2 * v, vl, vm), query(x, l, r, 2 * v + 1, vm, vr)); // item merge
    }

    // set element i to val
    void update(int i, Line val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (vr - vl == 1) a[v].add(val.a, val.b); // item update
        else {
            int vm = (vl + vr) / 2;
            if (i < vm) update(i, val, 2 * v, vl, vm);
            else update(i, val, 2 * v + 1, vm, vr);
            a[v].add(val.a, val.b); // node merge
        }
    }
};

struct P {
    ll x, y;
};

int N, M;
vector<P> A;
St st;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    A.resize(N);
    rep(i, N) cin >> A[i].x >> A[i].y;
    cin >> M;
    st = {M};
    rep(j, M) {
        ll a, b;
        cin >> a >> b;
        st.update(j, {a, b, 0});
    }

    vector<set<int>> ans(M + 1);
    rep(i, N) {
        P p = A[i];
        int l = 0, r = M;
        while (l != r) {
            int m = (l + r) / 2;
            if (st.query(p.x, 0, m + 1) > p.y) r = m;
            else l = m + 1;
        }

        ans[l].insert(i);
    }

    rep(j, M) {
        cout << ans[j].size();
        for (int i : ans[j]) cout << " " << i + 1;
        cout << "\n";
    }
}
