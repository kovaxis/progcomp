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

const int MOD = 998244353;

int add(int a, int b) {
    return (a + b) % MOD;
}

int sub(int a, int b) {
    return (a - b + MOD) % MOD;
}

int mul(int a, int b) {
    return (ll)a * b % MOD;
}

int binexp(int a, int m) {
    assert(m >= 0);
    int res = 1 % MOD;
    while (m) {
        if (m & 1) res = mul(res, a);
        a = mul(a, a);
        m >>= 1;
    }
    return res;
}

// compute the modular multiplicative inverse, assuming M is prime.
int multinv(int a) { return binexp(a, MOD - 2); }

vector<int> phalf, ptwo, D2, D2acc;

template <class T>
struct Stl {
    // immediate (result of querying in the segment)
    // lazy (value that has not been pushed to the children)
    vector<pair<T, T>> node;

    void reset(int N) { node.assign(4 * N, {0, 0}); }

    // helper: propagate lazy values in vertex `v` to both of its children
    void push(int v, int vl, int vr) {
        int vm = (vl + vr) / 2;
        T &lazy = node[v].second;
        auto &l = node[2 * v], &r = node[2 * v + 1];
        l.first = add(l.first, mul(lazy, sub(D2acc[vm], D2acc[vl]))); // update-op & query-op mix
        l.second = add(l.second, lazy);                               // update-op
        r.first = add(r.first, mul(lazy, sub(D2acc[vr], D2acc[vm]))); // update-op & query-op mix
        r.second = add(r.second, lazy);                               // update-op
        lazy = 0;                                                     // update-zero
    }

    // update range [l, r) using val
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l >= vr || r <= vl || r <= l) return;
        if (l == vl && r == vr) {
            node[v].first = add(node[v].first, mul(val, sub(D2acc[vr], D2acc[vl]))); // update-op & query-op mix
            node[v].second = add(node[v].second, val);                               // update-op
            return;
        }
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        update(l, min(r, vm), val, 2 * v, vl, vm);
        update(max(l, vm), r, val, 2 * v + 1, vm, vr);
        node[v].first = add(node[2 * v].first, node[2 * v + 1].first); // query-op
    }

    // query range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l <= vl && r >= vr) return node[v].first;
        int vm = (vl + vr) / 2;
        T val = 0; // query-zero
        if (l >= vr || r <= vl || r <= l) return val;
        push(v, vl, vr);
        val = add(val, query(l, min(r, vm), 2 * v, vl, vm));     // query-op
        val = add(val, query(max(l, vm), r, 2 * v + 1, vm, vr)); // query-op
        return val;
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
            op(pos[top[v]], pos[v] + 1);
            v = parent[top[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(pos[u], pos[v] + 1); // value on vertex
        // op(pos[u]+1, pos[v]+1); // value on path
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
        T ans = 0;                                                          // neutral element
        path(u, v, [&](int l, int r) { ans = add(ans, seg.query(l, r)); }); // query op
        return ans;
    }
};

// In the context of setting A[u] = k
// A[u]: before change
// A'[u]: after change
// arr[v] = sum_{w in V} A[w] * 2^-d(v, w)
// S = sum_{v in V} A[v] * arr[v]
// ans = 2^(N-1) * S
//
// arr'[v] = arr[v] + (A'[u] - A[u]) * 2^-d(v, u)
//
// S' = S + (A'[u] - A[u]) * (2*arr'[u] - (A'[u] - A[u]))
// arr[u] = 2^-d(u) * (2^-2 * b[root] + (1 - 2^-2) * sum_{v in anc(u)} b[v])
// b[u] = 2^(2*d(u)) * sum_{v in sub(u)} A[v] * 2^-d(v)

int N, Q;
vector<int> A, Atmp;

int S;

vector<vector<int>> G;
Hld hld;
Stl<int> b;

// set A[u] = k
void process_query(int u, int k) {
    int delta = sub(k, A[u]);
    cerr << "modifying A[" << u << "] from " << A[u] << " to " << k << endl;
    A[u] = k;

    // update b[v] for all affected nodes
    int bdelta = mul(delta, phalf[hld.depth[u]]);
    hld.update(b, 0, u, bdelta);

    // calculate new arr'[u]
    int root_factor = mul(phalf[2], hld.query<int>(b, 0, 0));
    int path_factor = mul(sub(1, multinv(4)), hld.query<int>(b, 0, u));
    int arr_u = mul(phalf[hld.depth[u]], add(root_factor, path_factor));

    // calculate new S' using arr'[u]
    S = add(S, mul(delta, sub(mul(2, arr_u), delta)));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    A.resize(N);
    Atmp.resize(N);
    G.assign(N, {});
    rep(i, N) cin >> Atmp[i];
    rep(j, N - 1) {
        int u, v;
        cin >> u >> v;
        G[u - 1].push_back(v - 1);
        G[v - 1].push_back(u - 1);
    }

    {
        int n = max(2 * N, 16);
        phalf.resize(n + 1);
        phalf[0] = 1;
        rep(i, n) phalf[i + 1] = mul(phalf[i], multinv(2));
        ptwo.resize(n + 1);
        ptwo[0] = 1;
        rep(i, n) ptwo[i + 1] = mul(ptwo[i], 2);
    }

    hld.init(G);
    D2.resize(N);
    D2acc.resize(N + 1);
    rep(u, N) D2[hld.pos[u]] = ptwo[2 * hld.depth[u]];
    rep(u, N) D2acc[u + 1] = add(D2acc[u], D2[u]);
    b.reset(N);

    rep(u, N) process_query(u, Atmp[u]);

    rep(qi, Q) {
        int u, k;
        cin >> u >> k;
        u -= 1;

        process_query(u, k);

        cout << mul(ptwo[N - 1], S) << "\n";
    }
}
