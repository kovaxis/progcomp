#include "../common.h"

struct NodeSum {
    ll x;

    NodeSum() : x(0) {}
    NodeSum(ll x) : x(x) {}
    NodeSum(NodeSum l, NodeSum r) : x(l.x + r.x) {}
};

struct NodeMin {
    ll x;

    NodeMin() : x(1e18) {}
    NodeMin(ll x) : x(x) {}
    NodeMin(NodeMin l, NodeMin r) : x(min(l.x, r.x)) {}
};

struct NodeMax {
    ll x;

    NodeMax() : x(-1e18) {}
    NodeMax(ll x) : x(x) {}
    NodeMax(NodeMax l, NodeMax r) : x(max(l.x, r.x)) {}
};

template <class Node>
struct St {
    vector<Node> node;

    void reset(int N) { node.assign(4 * N, {}); }

    template <class T>
    void build(const vector<T> &a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size()), vr = vr == -1 ? node.size() / 4 : vr;
        if (vr - vl == 1) {
            node[v] = {a[vl]}; // construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v, vl, vm);
        build(a, 2 * v + 1, vm, vr);
        node[v] = {node[2 * v], node[2 * v + 1]}; // query op
    }

    // query for range [l, r)
    Node query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l <= vl && r >= vr) return node[v];
        int vm = (vl + vr) / 2;
        Node val = {}; // neutral element
        if (l >= vr || r <= vl) return val;
        val = {query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr)}; // query op
        return val;
    }

    // set element i to val
    void update(int i, Node val, int v = 1, int vl = 0, int vr = -1) {
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
        node[v] = {node[2 * v], node[2 * v + 1]}; // query op
    }
};
