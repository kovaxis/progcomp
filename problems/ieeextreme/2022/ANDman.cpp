#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll MOD = 1000000007;

template <class T>
struct StMul {
    vector<T> node;

    void reset(int N) { node.assign(4 * N, 0); }

    void build(const vector<T> &a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size());
        if (vr == -1) vr = node.size() / 4;
        if (vr - vl == 1) {
            node[v] = a[vl]; // construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v, vl, vm);
        build(a, 2 * v + 1, vm, vr);
        node[v] = node[2 * v] * node[2 * v + 1] % MOD; // query op
    }

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l == vl && r == vr) return node[v];
        int vm = (vl + vr) / 2;
        T val = 1; // neutral element
        if (l >= vr || r <= vl) return val;
        val = val * query(l, min(r, vm), 2 * v, vl, vm) % MOD;     // query op
        val = val * query(max(l, vm), r, 2 * v + 1, vm, vr) % MOD; // query op
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
        node[v] = node[2 * v] * node[2 * v + 1] % MOD; // query op
    }
};

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
    void path(int u, int v, OP op) {
        while (top[u] != top[v]) {
            if (depth[top[u]] > depth[top[v]]) swap(u, v);
            op(pos[top[v]], pos[v]);
            v = parent[top[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(pos[u], pos[v]); // value on vertex
        // op(pos[u]+1, pos[v]); // value on path
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
        T ans = 1;                                                                // neutral element
        path(u, v, [&](int l, int r) { ans = ans * seg.query(l, r + 1) % MOD; }); // query op
        return ans;
    }
};

int N;
vector<vector<int>> G;
vector<ll> initial_w;
StMul<ll> w;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        initial_w.resize(N);
        rep(i, N) cin >> initial_w[i];
        G.assign(N, {});
        rep(j, N - 1) {
            int u, v;
            cin >> u >> v;
            G[u - 1].push_back(v - 1);
            G[v - 1].push_back(u - 1);
        }

        Hld hld;
        hld.init(G);
        w.reset(N);
        rep(i, N) {
            hld.update(w, i, initial_w[i]);
        }
        int Q;
        cin >> Q;
        rep(q, Q) {
            ll t, u, v;
            cin >> t >> u >> v;
            if (t == 1) {
                // update
                hld.update(w, u - 1, v);
            } else if (t == 2) {
                // query
                ll ans = hld.query<ll>(w, u - 1, v - 1);
                cout << ans << "\n";
            }
        }
    }
}
