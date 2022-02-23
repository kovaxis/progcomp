#include "../common.h"

template <class T>
struct Stl {
    // immediate (result of querying in the segment)
    // lazy (value that has not been pushed to the children)
    vector<pair<T, T>> node;

    Stl() {}
    void resize(int N) { node.resize(4 * N); }

    void build(const vector<T>& a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size());
        if (vr == -1) vr = node.size() / 4;
        if (vl == vr) {
            node[v].first = a[vl];  // construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v, vl, vm);
        build(a, 2 * v + 1, vm, vr);
        node[v].first = node[2 * v].first + node[2 * v + 1].first;  // query op
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
        if (l <= vl && r >= vr) {
            return node[v].first;
        }
        int vm = (vl + vr) / 2;
        T val = 0;  // query-zero
        if (l >= vr || r <= vl || r <= l) return val;
        push(v, vl, vr);
        val += query(l, min(r, vm), 2 * v, vl, vm);      // query-op
        val += query(max(l, vm), r, 2 * v + 1, vm, vr);  // query-op
        return val;
    }
};

#ifndef NOMAIN_SEGTREELAZY

Stl<ll> seg;

void que(int l, int r, ll ex) {
    ll out = seg.query(l - 1, r);
    cout << "[" << l << ", " << r << "] = " << out << endl;
    if (out != ex) {
        cout << "expected " << ex << ", got " << out << endl;
        assert(out == ex);
    }
}

void upd(int l, int r, ll v) {
    cout << "updating [" << l << ", " << r << "] with " << v << endl;
    seg.update(l - 1, r, v);
}

int main() {
    seg.resize(1000);

    que(1, 1000, 0);
    que(50, 40, 0);
    upd(3, 4, 1);
    que(-10, -100, 0);
    que(1, 100, 2);
    que(50, 40, 0);
    upd(1, 500, 2);
    que(100, 200, 202);
    que(50, 40, 0);
    que(1, 100, 202);
    que(-10, -100, 0);
    que(501, 1000, 0);
    upd(401, 1000, 10);
    que(50, 40, 0);
    que(2000, 1500, 0);
    que(1, 400, 802);
    que(401, 900, 200 + 5000);
    que(50, 40, 0);
    que(1000, 1, 0);
    que(-10, -100, 0);
}

#endif
