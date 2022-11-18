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

struct Hld {
    vector<int> parent, heavy, depth, pos, top;

    Hld() {}
    void init(vector<vector<int>> &G) {
        int N = G.size();
        parent.resize(N), heavy.resize(N), depth.resize(N), pos.resize(N),
            top.resize(N);
        depth[0] = -1, dfs(G, 0);
        int t = 0;
        rep(i, N) if (heavy[parent[i]] != i) {
            int j = i;
            while (j != -1) {
                top[j] = i, pos[j] = t++;
                j = heavy[j];
            }
        }
    }

    int dfs(vector<vector<int>> &G, int i) {
        int w = 1, mw = 0;
        depth[i] = depth[parent[i]] + 1, heavy[i] = -1;
        for (int c : G[i]) {
            if (c == parent[i]) continue;
            parent[c] = i;
            int sw = dfs(G, c);
            if (sw > mw) heavy[i] = c, mw = sw;
            w += sw;
        }
        return w;
    }

    template <class OP>
    int path(int u, int v, OP op) {
        while (top[u] != top[v]) {
            if (depth[top[u]] > depth[top[v]]) swap(u, v);
            op(pos[top[v]], pos[v] + 1);
            v = parent[top[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(pos[u], pos[v] + 1); // value on vertex
        // op(pos[u]+1, pos[v] + 1); // value on path
        return u;
    }

    int lca(int u, int v) {
        return path(u, v, [](int u, int v) {});
    }

    // segment tree
    template <class T, class S>
    void update(S &seg, int i, T val) {
        seg.update(pos[i], val);
    }

    // segment tree lazy
    template <class T, class S>
    void update(S &seg, int u, int v, T val) {
        path(u, v, [&](int l, int r) { seg.update(l, r, val); });
    }

    template <class T, class S>
    T query(S &seg, int u, int v) {
        T ans = 0;                                                 // neutral element
        path(u, v, [&](int l, int r) { ans += seg.query(l, r); }); // query op
        return ans;
    }
};

struct NodeSumSum {
    ll x, z;

    NodeSumSum(ll x) : x(x), z(0) {}
    NodeSumSum() : NodeSumSum(0) {}
    NodeSumSum(NodeSumSum l, NodeSumSum r) : NodeSumSum(l.x + r.x) {}

    void update(NodeSumSum val, int l, int r) { x += val.x * (r - l), z += val.x; }
    ll &lazy() { return z; }
};

template <class T, class Node>
struct Stl {
    vector<Node> node;

    void reset(int N) { node.assign(4 * N, {}); }

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
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        // cerr << "querying for range [" << l << ", " << r << ") in node [" << vl << ", " << vr << ")" << endl;
        if (l <= vl && r >= vr) return node[v].x;
        T val = {}; // neutral element
        if (l >= vr || r <= vl) return val;
        int vm = (vl + vr) / 2;
        push(v, vl, vm, vr);
        val = query(l, r, 2 * v, vl, vm) + query(l, r, 2 * v + 1, vm, vr); // query op
        return val;
    }

    // update range [l, r) using val
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
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

const int D = 21;

int N;
vector<vector<int>> G;

Hld hld;
Stl<ll, NodeSumSum> a[D];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    G.resize(N + D);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u += -1 + D, v += -1 + D;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    rep(d, D) {
        G[d].push_back(d + 1);
        G[d + 1].push_back(d);
    }

    hld.init(G);
    rep(d, D) a[d].reset(N + D);

    int Q;
    cin >> Q;
    rep(q, Q) {
        int t;
        cin >> t;
        if (t == 1) {
            // ask
            int u;
            cin >> u;
            u += -1 + D;

            cerr << "calculating contribution for node " << u + 1 - D << endl;
            ll ans = 0;
            repx(d, 0, D) {
                cerr << "  parent " << d << " contributes with " << hld.query<ll>(a[d], u, u) << endl;
                ans += hld.query<ll>(a[d], u, u);
                u = hld.parent[u];
            }
            cerr << "  total = " << ans << endl;

            cout << ans << "\n";
        } else if (t == 2) {
            // update
            int u, v;
            ll k, d;
            cin >> u >> v >> k >> d;
            u += -1 + D, v += -1 + D;

            cerr << "updating path " << u + 1 - D << " to " << v + 1 - D << " with k = " << k << " for distance " << d << endl;
            cerr << "  A[entire path][" << d << "] += k" << endl;
            hld.update(a[d], u, v, k);
            int top = hld.lca(u, v);
            while (d > 0) {
                d -= 1;
                int p = hld.parent[top];
                cerr << "  A[" << top + 1 - D << "][" << d << "] += k" << endl;
                cerr << "  A[" << p + 1 - D << "][" << d << "] += k" << endl;
                hld.update(a[d], top, p, k);
                top = p;
            }
        }
    }
}
