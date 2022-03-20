#include "../common.h"

template <class T>
struct StSum {
    vector<T> node;

    void reset(int N) { node.assign(4 * N, 0); }

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
        node[v] = node[2 * v] + node[2 * v + 1];  // query op
    }

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l == vl && r == vr) return node[v];
        int vm = (vl + vr) / 2;
        T val = 0;  // neutral element
        if (l >= vr || r <= vl) return val;
        val += query(l, min(r, vm), 2 * v, vl, vm);      // query op
        val += query(max(l, vm), r, 2 * v + 1, vm, vr);  // query op
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
        node[v] = node[2 * v] + node[2 * v + 1];  // query op
    }
};

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

#ifndef NOMAIN_SEGTREE

template <class T, class U, class OP>
void test_segt(string name, T segt, U neutral, OP op, int N, int M) {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<U> a(N);
    rep(i, N) a[i] = U((int32_t)rng());

    cerr << "testing " << name << "... " << flush;
    segt.build(a);
    rep(i, M) {
        int l = rng() % (N + 1);
        int r = rng() % (N + 1);
        U ex = neutral;
        rep(i, l, r) op(ex, a[i]);
        U res = segt.query(l, r);
        assert(res == ex);

        int j = rng() % N;
        a[j] = (U)rng();
        segt.update(j, a[j]);
    }
    cerr << "ok" << endl;
}

int main() {
    static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    int N = 10000;
    int M = 10000;

    test_segt(
        "StSum", StSum<ll>(), (ll)0, [](ll& a, ll b) { a += b; }, N, M);
    test_segt(
        "StMax", StMax<ll>(), -INF, [](ll& a, ll b) { a = max(a, b); }, N, M);
    test_segt(
        "StMin", StMin<ll>(), INF, [](ll& a, ll b) { a = min(a, b); }, N, M);
}

#endif
