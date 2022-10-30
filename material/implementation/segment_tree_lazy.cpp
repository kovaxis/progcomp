#include "../common.h"

struct NodeSumSum {
    ll x, z;

    NodeSumSum(ll x) : x(x), z(0) {}
    NodeSumSum() : NodeSumSum(0) {}
    NodeSumSum(NodeSumSum l, NodeSumSum r) : NodeSumSum(l.x + r.x) {}

    void update(NodeSumSum val, int l, int r) { x += val.x * (r - l), z += val.x; }
    ll &lazy() { return z; }
};

struct NodeSetSum {
    ll x, z;

    NodeSetSum(ll x) : x(x), z(INT64_MAX) {}
    NodeSetSum() : NodeSetSum(0) {}
    NodeSetSum(NodeSetSum l, NodeSetSum r) : NodeSetSum(l.x + r.x) {}

    void update(NodeSetSum val, int l, int r) {
        if (val.x != INT64_MAX) x = val.x * (r - l), z = val.x;
    }
    ll &lazy() { return z; }
};

struct NodeSumMin {
    ll x, z;

    NodeSumMin(ll x) : x(x), z(0) {}
    NodeSumMin() : NodeSumMin(1e18) {}
    NodeSumMin(NodeSumMin l, NodeSumMin r) : NodeSumMin(min(l.x, r.x)) {}

    void update(NodeSumMin val, int l, int r) { x += val.x, z += val.x; }
    ll &lazy() { return z; }
};

template <class Node>
struct Stl {
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

    void push(int v, int vl, int vm, int vr) {
        Node lazy;
        swap(lazy.lazy(), node[v].lazy());
        node[2 * v].update(lazy.lazy(), vl, vm);
        node[2 * v + 1].update(lazy.lazy(), vm, vr);
    }

    // query for range [l, r)
    Node query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        // cerr << "querying for range [" << l << ", " << r << ") in node [" << vl << ", " << vr << ")" << endl;
        if (l <= vl && r >= vr) return node[v];
        Node val = {}; // neutral element
        if (l >= vr || r <= vl) return val;
        int vm = (vl + vr) / 2;
        push(v, vl, vm, vr);
        val = {query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr)}; // query op
        return val;
    }

    // update range [l, r) using val
    void update(int l, int r, Node val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l >= vr || r <= vl || r <= l) return;
        if (l <= vl && r >= vr) {
            node[v].update(val, vl, vr); // update-op & query-op mix
            return;
        }
        int vm = (vl + vr) / 2;
        push(v, vl, vm, vr);
        update(l, r, val, 2 * v, vl, vm);
        update(l, r, val, 2 * v + 1, vm, vr);
        node[v] = {node[2 * v], node[2 * v + 1]}; // query-op & update-zero
    }
};
