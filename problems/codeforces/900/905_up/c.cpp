#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

template <class T>
struct StlMax {
    int n;
    vector<T> a, b;

    T qneut() { return {-2e18, 0}; }
    T uneut() { return {0, 0}; }
    T merge(T x, T y) { return max(x, y); }
    void upd(int v, T x, int l, int r) {
        a[v].first += x.first, b[v].first += x.first;
        a[v].second += x.second, b[v].second += x.second;
    }

    StlMax(int n = 0) : n(n), a(4 * n, qneut()), b(4 * n, uneut()) {}

    void push(int v, int vl, int vm, int vr) {
        upd(2 * v, b[v], vl, vm);
        upd(2 * v + 1, b[v], vm, vr);
        b[v] = uneut();
    }

    // compute the query operation for the range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = 1e9) {
        vr = min(vr, n);
        if (l <= vl && r >= vr) return a[v];
        if (l >= vr || r <= vl) return qneut();
        int vm = (vl + vr) / 2;
        push(v, vl, vm, vr);
        return merge(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr));
    }

    // apply update operation to range [l, r)
    void update(int l, int r, T x, int v = 1, int vl = 0, int vr = 1e9) {
        vr = min(vr, n);
        if (l >= vr || r <= vl || r <= l) return;
        if (l <= vl && r >= vr) upd(v, x, vl, vr);
        else {
            int vm = (vl + vr) / 2;
            push(v, vl, vm, vr);
            update(l, r, x, 2 * v, vl, vm);
            update(l, r, x, 2 * v + 1, vm, vr);
            a[v] = merge(a[2 * v], a[2 * v + 1]);
        }
    }
};

template <class T>
struct StlMin {
    int n;
    vector<T> a, b;

    T qneut() { return {2e18, 0}; }
    T uneut() { return {0, 0}; }
    T merge(T x, T y) { return min(x, y); }
    void upd(int v, T x, int l, int r) {
        a[v].first += x.first, b[v].first += x.first;
        a[v].second += x.second, b[v].second += x.second;
    }

    StlMin(int n = 0) : n(n), a(4 * n, qneut()), b(4 * n, uneut()) {}

    void push(int v, int vl, int vm, int vr) {
        upd(2 * v, b[v], vl, vm);
        upd(2 * v + 1, b[v], vm, vr);
        b[v] = uneut();
    }

    // compute the query operation for the range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = 1e9) {
        vr = min(vr, n);
        if (l <= vl && r >= vr) return a[v];
        if (l >= vr || r <= vl) return qneut();
        int vm = (vl + vr) / 2;
        push(v, vl, vm, vr);
        return merge(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr));
    }

    // apply update operation to range [l, r)
    void update(int l, int r, T x, int v = 1, int vl = 0, int vr = 1e9) {
        vr = min(vr, n);
        if (l >= vr || r <= vl || r <= l) return;
        if (l <= vl && r >= vr) upd(v, x, vl, vr);
        else {
            int vm = (vl + vr) / 2;
            push(v, vl, vm, vr);
            update(l, r, x, 2 * v, vl, vm);
            update(l, r, x, 2 * v + 1, vm, vr);
            a[v] = merge(a[2 * v], a[2 * v + 1]);
        }
    }
};

struct Op {
    int q, d;
};

const ll INF = 1e18;

int N, Q;
vector<int> Ainit, L, R, D;
StlMax<pair<ll, int>> mx;
StlMin<pair<ll, int>> mn;
vector<vector<Op>> B;
vector<ll> ans;

void solve() {
    mx = {Q + 1};
    mn = {Q + 1};
    rep(q, Q + 1) {
        mx.update(q, q + 1, {0ll - mx.query(q, q + 1).first, q});
        mn.update(q, q + 1, {0ll - mn.query(q, q + 1).first, q});
    }

    B.assign(N+1, {});
    rep(q, Q) {
        B[L[q]].push_back({q + 1, D[q]});
        B[R[q]].push_back({q + 1, -D[q]});
    }

    ans.resize(N);

    rep(i, N) {
        mx.update(0, Q + 1, {Ainit[i], 0});
        mn.update(0, Q + 1, {Ainit[i], 0});

        for (Op op : B[i]) {
            mx.update(op.q, Q + 1, {op.d, 0});
            mn.update(op.q, Q + 1, {op.d, 0});
        }

        while (mx.query(0, Q + 1).first > mn.query(0, Q + 1).first) {
            int q = mx.query(0, Q + 1).second;
            mx.update(q, q + 1, {-INF, 0});
            mn.update(q, q + 1, {INF, 0});
        }

        ans[i] = mn.query(0, Q + 1).first;

        mx.update(0, Q + 1, {-Ainit[i], 0});
        mn.update(0, Q + 1, {-Ainit[i], 0});
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        Ainit.resize(N);
        rep(i, N) cin >> Ainit[i];
        cin >> Q;
        L.resize(Q), R.resize(Q), D.resize(Q);
        rep(q, Q) cin >> L[q] >> R[q] >> D[q];
        rep(q, Q) L[q] -= 1;
        solve();
        rep(i, N) cout << ans[i] << " ";
        cout << "\n";
    }
}
