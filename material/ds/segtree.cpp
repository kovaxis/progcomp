#include "../common.h"

template <class T>
struct St {
    vector<T> node;

    St() {}
    void resize(int N) { node.resize(4 * N); }

    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (l == vl && r == vr) return node[v];
        int vm = (vl + vr) / 2;
        T val = 0;  // neutral element
        if (l <= vm) val += query(l, min(r, vm), 2 * v, vl, vm);  // query op
        if (r >= vm + 1)
            val += query(max(l, vm + 1), r, 2 * v + 1, vm + 1, vr);  // query op
        return val;
    }

    void update(int i, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4 - 1;
        if (vl == vr) {
            node[v] = val;
            return;
        }
        int vm = (vl + vr) / 2;
        if (i <= vm) {
            update(i, val, 2 * v, vl, vm);
        } else {
            update(i, val, 2 * v + 1, vm + 1, vr);
        }
        node[v] = node[2 * v] + node[2 * v + 1];  // query op
    }
};

/*
void build(const vector<T>& a, int v = 1, int vl = 0, int vr = -1) {
    node.resize(4 * a.size());
    if (vr == -1) vr = node.size() / 4 - 1;
    if (vl == vr) {
        node[v] = a[vl];  // construction
        return;
    }
    int vm = (vl + vr) / 2;
    build(a, 2 * v, vl, vm);
    build(a, 2 * v + 1, vm + 1, vr);
    node[v] = node[2 * v] + node[2 * v + 1];  // query op
}
*/

#ifndef NOMAIN_SEGTREE

St<int> segt;

void query(int l, int r, int ex) {
    int out = segt.query(l - 1, r - 1);
    cerr << "sum [" << l << ", " << r << "] = " << out << endl;
    assert(out == ex);
}

int main() {
    vector<int> a(20);
    rep(i, 1, 21) a[i - 1] = i;
    random_shuffle(a.begin(), a.end());
    for (int b : a) cerr << b << " ";
    cerr << endl;

    segt.resize(20);
    rep(i, 20) segt.update(i, a[i]);

    query(1, 20, 210);
    query(1, 10, 90);
    query(2, 7, 36);
    query(18, 20, 31);
    query(20, 20, 18);
    query(1, 1, 13);
    query(9, 9, 5);
    query(1, 8, 69);

    a[3] = -10;
    segt.update(3, -10);
    a[19] = -20;
    segt.update(19, -20);
    for (int b : a) cerr << b << " ";
    cerr << endl;
    query(1, 20, 159);
    query(1, 10, 77);
    query(2, 7, 23);
    query(18, 20, -7);
    query(20, 20, -20);
    query(1, 1, 13);
    query(9, 9, 5);
    query(1, 8, 56);
}

#endif
