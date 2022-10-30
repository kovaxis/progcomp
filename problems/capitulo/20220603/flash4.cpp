#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

template <class T>
struct StlSumSum {
    // immediate (result of querying in the segment)
    // lazy (value that has not been pushed to the children)
    vector<pair<T, T>> node;

    void reset(int N) { node.assign(4 * N, {0, 0}); }

    void build(const vector<T>& a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size());
        if (vr == -1) vr = node.size() / 4;
        if (vr - vl == 1) {
            node[v].first = a[vl];  // construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v, vl, vm);
        build(a, 2 * v + 1, vm, vr);
        node[v].first = node[2 * v].first + node[2 * v + 1].first;  // query op
        node[v].second = 0;  // update-zero
    }

    // helper: propagate lazy values in vertex `v` to both of its children
    void push(int v, int vl, int vr) {
        int vm = (vl + vr) / 2;
        T& lazy = node[v].second;
        node[2 * v].first += lazy * (vm - vl);      // update-op & query-op mix
        node[2 * v].second += lazy;                 // update-op
        node[2 * v + 1].first += lazy * (vr - vm);  // update-op & query-op mix
        node[2 * v + 1].second += lazy;             // update-op
        lazy = 0;                                   // update-zero
    }

    // update range [l, r) using val
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l >= vr || r <= vl || r <= l) return;
        if (l == vl && r == vr) {
            node[v].first += val * (vr - vl);  // update-op & query-op mix
            node[v].second += val;             // update-op
            return;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        update(l, min(r, vm), val, 2 * v, vl, vm);
        update(max(l, vm), r, val, 2 * v + 1, vm, vr);
        node[v].first = node[2 * v].first + node[2 * v + 1].first;  // query-op
    }

    // query range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l <= vl && r >= vr) return node[v].first;
        int vm = (vl + vr) / 2;
        T val = 0;  // query-zero
        if (l >= vr || r <= vl || r <= l) return val;
        push(v, vl, vr);
        val += query(l, min(r, vm), 2 * v, vl, vm);      // query-op
        val += query(max(l, vm), r, 2 * v + 1, vm, vr);  // query-op
        return val;
    }
};

int N, M;

vector<int> stk, order, b, ainv, ctmp;
StlSumSum<int> costs;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        stk.resize(N), ainv.resize(N), b.resize(M), order.resize(M);
        rep(i, N) cin >> stk[i];
        rep(i, N) stk[i]--;
        rep(i, N) ainv[stk[i]] = i;
        rep(i, M) cin >> b[i];
        rep(i, M) order[i] = ainv[b[i]];

        rep(i, N) ctmp[i] = 2 * i + 1;
        costs.build(ctmp);

        rep(j, M) { int i = order[j]; }
    }
}
