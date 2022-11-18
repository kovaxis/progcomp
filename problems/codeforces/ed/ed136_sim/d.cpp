#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Node {
    pair<ll, int> x;
    ll lazy;

    Node(int i) : x({neutral(), i}), lazy(0) {} // query neutral, update neutral
    Node(ll x_, int i) : Node(i) { x.first = x_; }
    Node(Node &l, Node &r) : Node(0) { refresh(l, r); }     // node merge construction
    void refresh(Node &l, Node &r) { x = merge(l.x, r.x); } // node merge

    void update(ll val, int l, int r) { x.first += val, lazy += val; } // update-query, update accumulate
    ll take() {
        ll z = 0; // update neutral
        swap(lazy, z);
        return z;
    }

    pair<ll, int> query() { return x; }
    static ll neutral() { return 0; }                                                  // query neutral
    static pair<ll, int> merge(pair<ll, int> l, pair<ll, int> r) { return max(l, r); } // query merge
};

template <class T, class Node>
struct Stl {
    vector<Node> node;

    void reset(int N) { node.assign(4 * N, {}); } // node neutral

    void build(const vector<T> &a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size()), vr = vr == -1 ? node.size() / 4 : vr;
        if (vr - vl == 1) {
            node[v] = {a[vl]}; // node construction
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v, vl, vm);
        build(a, 2 * v + 1, vm, vr);
        node[v] = {node[2 * v], node[2 * v + 1]}; // node merge construction
    }

    void push(int v, int vl, int vm, int vr) {
        T lazy = node[v].take();              // update neutral
        node[2 * v].update(lazy, vl, vm);     // node update
        node[2 * v + 1].update(lazy, vm, vr); // node update
    }

    // query for range [l, r)
    T query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l <= vl && r >= vr) return node[v].query(); // query op
        if (l >= vr || r <= vl) return Node::neutral(); // query neutral
        int vm = (vl + vr) / 2;
        push(v, vl, vm, vr);
        return Node::merge(query(l, r, 2 * v, vl, vm), query(l, r, 2 * v + 1, vm, vr)); // item merge
    }

    // update range [l, r) using val
    void update(int l, int r, T val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = node.size() / 4;
        if (l >= vr || r <= vl || r <= l) return;
        if (l <= vl && r >= vr) node[v].update(val, vl, vr); // node update
        else {
            int vm = (vl + vr) / 2;
            push(v, vl, vm, vr);
            update(l, r, val, 2 * v, vl, vm);
            update(l, r, val, 2 * v + 1, vm, vr);
            node[v].refresh(node[2 * v], node[2 * v + 1]); // node merge
        }
    }
};

int N, K, L;
vector<vector<int>> up;
vector<vector<int>> G;
vector<pair<int, int>> range;
int last_pos;
Stl3<int> D;

int dfs(int u) {
    range[u].first = last_pos;
    last_pos += 1;
    for (int v : G[u]) dfs(v);
    range[u].second = last_pos;
    D.update(range[u].first + 1, range[u].second, 1);
}

int go_up(int u, int cnt) {
    int l = 0;
    while (cnt) {
        if (cnt & 1) u = up[l][u];
        cnt >>= 1;
        l += 1;
    }
    return u;
}

// can we use K ops to reach a height <= h?
bool can_reach(int h) {
    rep(k, K) {
        auto [mxd, mxi] = D.query(0, N);
        int relocate = go_up(mxi, h - 1);
        int rdepth = D.query(range[relocate].first, range[relocate].first + 1).first;
        D.update(range[relocate].first, range[relocate].second, -rdepth + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> K;

        L = N <= 1 ? 0 : 32 - __builtin_clz(N - 1);
        up.resize(L + 1, vector<int>(N));

        G.assign(N, {});
        rep(i, N - 1) {
            int p;
            cin >> p;
            p -= 1;

            up[0][i + 1] = p;
            G[p].push_back(i + 1);
        }

        rep(l, L) rep(i, N) up[l + 1][i] = up[l][up[l][i]];

        D.reset(N);
        dfs(0);

        int l = 1, r = N - 1;
        while (l != r) {
            int m = (l + r) / 2;
            if (can_reach(m)) r = m;
            else l = m + 1;
        }

        cout << l << "\n";
    }
}
