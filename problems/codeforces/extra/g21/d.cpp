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

const ll INF = 1e18;

template <class T>
struct StMax {
    vector<T> node;

    void reset(int N) { node.assign(4 * N, -INF); }

    void build(const vector<T>& a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size());
        if (vr == -1) vr = node.size() / 4;
        if (vr - vl == 1) {
            node[v] = a[vl];  // construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v, vl, vm);
        build(a, 2 * v + 1, vm, vr);
        node[v] = max(node[2 * v], node[2 * v + 1]);  // query op
    }

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l == vl && r == vr) return node[v];
        int vm = (vl + vr) / 2;
        T val = -INF;  // neutral element
        if (l >= vr || r <= vl) return val;
        val = max(val, query(l, min(r, vm), 2 * v, vl, vm));      // query op
        val = max(val, query(max(l, vm), r, 2 * v + 1, vm, vr));  // query op
        return val;
    }

    // set element i to val
    void update(int i, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (vr - vl == 1) {
            node[v] = val;
            return;
        }
        int vm = (vl + vr) / 2;
        if (i < vm) {
            update(i, val, 2 * v, vl, vm);
        } else {
            update(i, val, 2 * v + 1, vm, vr);
        }
        node[v] = max(node[2 * v], node[2 * v + 1]);  // query op
    }
};

template <class T>
struct StMin {
    vector<T> node;

    void reset(int N) { node.assign(4 * N, INF); }

    void build(const vector<T>& a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size());
        if (vr == -1) vr = node.size() / 4;
        if (vr - vl == 1) {
            node[v] = a[vl];  // construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v, vl, vm);
        build(a, 2 * v + 1, vm, vr);
        node[v] = min(node[2 * v], node[2 * v + 1]);  // query op
    }

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l == vl && r == vr) return node[v];
        int vm = (vl + vr) / 2;
        T val = INF;  // neutral element
        if (l >= vr || r <= vl) return val;
        val = min(val, query(l, min(r, vm), 2 * v, vl, vm));      // query op
        val = min(val, query(max(l, vm), r, 2 * v + 1, vm, vr));  // query op
        return val;
    }

    // set element i to val
    void update(int i, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (vr - vl == 1) {
            node[v] = val;
            return;
        }
        int vm = (vl + vr) / 2;
        if (i < vm) {
            update(i, val, 2 * v, vl, vm);
        } else {
            update(i, val, 2 * v + 1, vm, vr);
        }
        node[v] = min(node[2 * v], node[2 * v + 1]);  // query op
    }
};

int N;
vector<ll> a;
StMin<ll> up, dn;
vector<int> upstk, dnstk;

ll solve() {
    upstk.clear(), up.reset(N);
    dnstk.clear(), dn.reset(N);

    invrep(i, N) {
        while (!upstk.empty() && a[i] > a[upstk.back()])
            up.update(upstk.back(), INF), upstk.pop_back();
        while (!dnstk.empty() && a[i] < a[dnstk.back()])
            dn.update(dnstk.back(), INF), dnstk.pop_back();
        ll upcost = up.query(i + 1, dnstk.empty() ? N : dnstk.back()) + 1;
        ll dncost = dn.query(i + 1, upstk.empty() ? N : upstk.back()) + 1;
        ll cost = min(upcost, dncost);
        if (i == N - 1) cost = 0;
        cerr << "cost to N from " << i + 1 << " = " << cost << endl;
        up.update(i, cost), upstk.push_back(i);
        dn.update(i, cost), dnstk.push_back(i);
    }

    return up.query(0, 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        a.resize(N);
        rep(i, N) cin >> a[i];

        cout << solve() << "\n";
    }
}
