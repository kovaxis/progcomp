#include "../common.h"

template <class T>
struct Stl {
    // immediate (result of querying in the segment)
    // lazy (value that has not been pushed to the children)
    vector<pair<T, T>> node;

    Stl() {}
    void resize(int N) { node.resize(4 * N); }

    // helper: propagate lazy values in vertex `v` to both of its children
    void push(int v, int vl, int vr) {
        int vm = (vl + vr) / 2;
        T& lazy = node[v].second;
        node[2 * v].first += lazy * (vm - vl + 1);  // update-op & query-op mix
        node[2 * v].second += lazy;                 // update-op
        node[2 * v + 1].first += lazy * (vr - vm);  // update-op & query-op mix
        node[2 * v + 1].second += lazy;             // update-op
        lazy = 0;                                   // update-zero
    }

    // apply the update operation to the range [l, r] (inclusive) in O(log N)
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l == vl && r == vr) {
            node[v].first += val * (vr - vl + 1);  // update-op & query-op mix
            node[v].second += val;                 // update-op
            return;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        if (l <= vm) update(l, min(r, vm), val, 2 * v, vl, vm);
        if (r >= vm + 1) update(max(l, vm + 1), r, val, 2 * v + 1, vm + 1, vr);
        node[v].first = node[2 * v].first + node[2 * v + 1].first;  // query-op
    }

    // apply the query operation to the range [l, r] (inclusive) in O(log N)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l <= vl && r >= vr) {
            return node[v].first;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        T val = 0;                                                // query-zero
        if (l <= vm) val += query(l, min(r, vm), 2 * v, vl, vm);  // query-op
        if (r >= vm + 1)
            val += query(max(l, vm + 1), r, 2 * v + 1, vm + 1, vr);  // query-op
        return val;
    }
};

/*
void build(const vector<T>& a, int v = 1, int vl = 0, int vr = -1) {
    node.resize(4 * a.size());
    if (vr == -1) vr = node.size() / 4 - 1;
    if (vl == vr) {
        node[v].first = a[vl];  // construction
        return;
    }
    int vm = (vl + vr) / 2;
    build(a, 2 * v, vl, vm);
    build(a, 2 * v + 1, vm + 1, vr);
    node[v].first = node[2 * v].first + node[2 * v + 1].first;  // query op
}
*/

#ifndef NOMAIN_SEGTREELAZY

Stl<ll> seg;

void que(int l, int r, ll ex) {
    ll out = seg.query(l - 1, r - 1);
    cout << "[" << l << ", " << r << "] = " << out << endl;
    if (out != ex) {
        cout << "expected " << ex << ", got " << out << endl;
        assert(out == ex);
    }
}

void upd(int l, int r, ll v) {
    cout << "updating [" << l << ", " << r << "] with " << v << endl;
    seg.update(l - 1, r - 1, v);
}

int main() {
    seg.resize(1000);

    que(1, 1000, 0);
    upd(3, 4, 1);
    que(1, 100, 2);
    upd(1, 500, 2);
    que(100, 200, 202);
    que(1, 100, 202);
    que(501, 1000, 0);
    upd(401, 1000, 10);
    que(1, 400, 802);
    que(401, 900, 200 + 5000);
}

#endif
