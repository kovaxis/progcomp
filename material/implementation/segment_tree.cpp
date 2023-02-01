#include "../common.h"

template <class T>
struct St3 {
    vector<T> a;

    T neutral() { return 0; }
    T merge(T l, T r) { return l + r; }

    St3() {}
    St3(int N) : a(4 * N, neutral()) {} // node neutral

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (l <= vl && r >= vr) return a[v]; // item construction
        int vm = (vl + vr) / 2;
        if (l >= vr || r <= vl) return neutral();                                 // item neutral
        return merge(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr)); // item merge
    }

    // set element i to val
    void update(int i, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (vr - vl == 1) a[v] = val; // item update
        else {
            int vm = (vl + vr) / 2;
            if (i < vm) update(i, val, 2 * v, vl, vm);
            else update(i, val, 2 * v + 1, vm, vr);
            a[v] = merge(a[2 * v], a[2 * v + 1]); // node merge
        }
    }
};

struct Node {
    ll x;

    Node() : x(neutral()) {}
    Node(ll x) : x(x) {} // optional
    Node(Node &l, Node &r) { refresh(l, r); }
    void refresh(Node &l, Node &r) { x = merge(l.x, r.x); }

    ll query() { return x; }
    void update(ll a) { x = a; }
    static ll neutral() { return 0; }
    static ll merge(ll l, ll r) { return l + r; }
};

template <class T, class Node>
struct St {
    vector<Node> node;

    void reset(int N) { node.assign(4 * N, {}); } // node neutral

    void build(const vector<T> &a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size()), vr = vr == -1 ? node.size() / 4 : vr;
        if (vr - vl == 1) node[v] = {a[vl]}; // node construction
        else {
            int vm = (vl + vr) / 2;
            build(a, 2 * v, vl, vm);
            build(a, 2 * v + 1, vm, vr);
            node[v] = {node[2 * v], node[2 * v + 1]}; // node merge & construction
        }
    }

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l <= vl && r >= vr) return node[v].query(); // item construction
        int vm = (vl + vr) / 2;
        if (l >= vr || r <= vl) return Node::neutral();                                 // item neutral
        return Node::merge(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr)); // item merge
    }

    // set element i to val
    void update(int i, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (vr - vl == 1) {
            node[v].update(val); // item update
            return;
        }
        int vm = (vl + vr) / 2;
        if (i < vm) {
            update(i, val, 2 * v, vl, vm);
        } else {
            update(i, val, 2 * v + 1, vm, vr);
        }
        node[v].refresh(node[2 * v], node[2 * v + 1]); // node merge
    }
};
