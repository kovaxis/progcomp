#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

struct bigint {
    vector<uint32_t> digits;

    bigint() {}
    bigint(ll x) : digits{lo(x), hi(x)} { this->trim(); }
    bigint(vector<uint32_t> d) : digits(d) {}

    static uint32_t lo(uint64_t dw) { return (uint32_t)dw; }
    static uint32_t hi(uint64_t dw) { return (uint32_t)(dw >> 32); }

    // remove leading zeros from representation
    void trim() {
        while (this->digits.size() && this->digits.back() == 0)
            this->digits.pop_back();
    }

    void operator+=(const bigint& rhs) {
        uint32_t c = 0;
        int ls = this->digits.size();
        int rs = rhs.digits.size();
        rep(i, max(ls, rs)) {
            if (i >= ls) this->digits.push_back(0);
            uint64_t r =
                (uint64_t)this->digits[i] + (i < rs ? rhs.digits[i] : 0) + c;
            this->digits[i] = lo(r), c = hi(r);
        }
        if (c != 0) this->digits.push_back(c);
    }

    void operator-=(const bigint& rhs) {
        uint32_t c = 1;
        int ls = this->digits.size();
        int rs = rhs.digits.size();
        rep(i, max(ls, rs)) {
            if (i >= ls) this->digits.push_back(0);
            uint64_t r =
                (uint64_t)this->digits[i] + ~(i < rs ? rhs.digits[i] : 0) + c;
            this->digits[i] = lo(r), c = hi(r);
        }
        if (c != 1) this->digits.push_back(c);
    }

    // unsigned multiplication
    void operator*=(const bigint& rhs) {
        static bigint lhs;
        swap(*this, lhs);
        this->digits.clear();
        rep(j, lhs.digits.size()) {
            uint64_t c = 0;
            int ls = this->digits.size();
            int rs = rhs.digits.size();
            rep(i, j, max(ls, rs + j)) {
                if (i >= ls) this->digits.push_back(0);
                uint64_t r = (uint64_t)this->digits[i] +
                             (uint64_t)(i - j < rs ? rhs.digits[i - j] : 0) *
                                 lhs.digits[j] +
                             c;
                this->digits[i] = lo(r), c = hi(r);
            }
            if (c != 0) this->digits.push_back(c);
        }
    }

    // compares `this` with `rhs`:
    //  `this < rhs`: -1
    //  `this == rhs`: 0
    //  `this > rhs`: 1
    int cmp(const bigint& rhs) {
        int ls = this->digits.size();
        int rs = rhs.digits.size();
        invrep(i, max(ls, rs)) {
            uint32_t l = i < ls ? this->digits[i] : 0;
            uint32_t r = i < rs ? rhs.digits[i] : 0;
            if (l < r)
                return -1;
            else if (l > r)
                return 1;
        }
        return 0;
    }

    bool operator==(const bigint& rhs) { return cmp(rhs) == 0; }
    bool operator!=(const bigint& rhs) { return cmp(rhs) != 0; }
    bool operator<(const bigint& rhs) { return cmp(rhs) == -1; }
    bool operator>=(const bigint& rhs) { return cmp(rhs) != -1; }
    bool operator>(const bigint& rhs) { return cmp(rhs) == 1; }
    bool operator<=(const bigint& rhs) { return cmp(rhs) != 1; }
};

template <class T>
struct St {
    vector<T> node;

    St() {}
    St(vector<T> a) { build(a); }

    void build(vector<T>& a, int v = 1, int vl = 0, int vr = -1) {
        node.resize(4 * a.size());
        if (vr == -1) vr = node.size() / 4 - 1;
        if (vl == vr) {
            node[v] = a[vl];
            return;
        }
        int vm = (vl + vr) / 2;
        build(a, 2 * v, vl, vm);
        build(a, 2 * v + 1, vm + 1, vr);
        node[v] = node[2 * v] + node[2 * v + 1];  // query op
    }

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
        node[v] = node[2 * v] + node[2 * v + 1];
    }
};

template <class T>
struct Stl {
    // immediate (result of querying in the segment)
    // lazy (value that has not been pushed to the children)
    vector<pair<T, T>> node;

    Stl() {}
    Stl(const vector<T>& a) { build(a); }

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

template <class T, class S>
struct Hld {
    S seg;
    vector<int> parent, heavy, depth, pos, top;

    Hld() {}
    Hld(vector<set<int>>& adj, const vector<T>& nodes) {
        int N = adj.size();
        parent.resize(N), heavy.resize(N), depth.resize(N), pos.resize(N),
            top.resize(N);
        seg = nodes;
        depth[0] = -1, dfs(adj, 0);
        int t = 0;
        rep(i, N) if (heavy[parent[i]] != i) {
            int j = i;
            while (j != -1) {
                top[j] = i, pos[j] = t++;
                j = heavy[j];
            }
        }
    }

    int dfs(vector<set<int>>& adj, int i) {
        int w = 1, mw = 0;
        depth[i] = depth[parent[i]] + 1, heavy[i] = -1;
        for (int c : adj[i]) {
            if (c == parent[i]) continue;
            parent[c] = i;
            int sw = dfs(adj, c);
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
        op(pos[u], pos[v]);  // value on vertex
        // op(pos[u]+1, pos[v]); // value on path
    }

    // segment tree
    // void update(int i, T val) { seg.update(pos[i], val); }

    // segment tree lazy
    void update(int u, int v, T val) {
        path(u, v, [&](int l, int r) { seg.update(l, r, val); });
    }

    T query(int u, int v) {
        T ans = 0;
        path(u, v, [&](int l, int r) { ans += seg.query(l, r); });
        return ans;
    }
};

// calculates the lowest common ancestor for any two nodes in O(log N) time,
// with O(N log N) preprocessing
struct Lca {
    int L;
    vector<vector<int>> up;
    vector<pair<int, int>> time;

    Lca() {}
    Lca(const vector<set<int>>& adj) {
        int N = adj.size();
        L = N <= 1 ? 0 : 32 - __builtin_clz(N - 1);
        up.resize(L + 1);
        rep(l, L + 1) up[l].resize(N);
        time.resize(N);
        int t = 0;
        visit(adj, 0, 0, t);
        rep(l, L) rep(i, N) up[l + 1][i] = up[l][up[l][i]];
    }

    void visit(const vector<set<int>>& adj, int i, int p, int& t) {
        up[0][i] = p;
        time[i].first = t++;
        for (int edge : adj[i]) {
            if (edge == p) continue;
            visit(adj, edge, i, t);
        }
        time[i].second = t++;
    }

    bool is_anc(int up, int dn) {
        return time[up].first <= time[dn].first &&
               time[dn].second <= time[up].second;
    }

    int get(int i, int j) {
        if (is_anc(i, j)) return i;
        if (is_anc(j, i)) return j;
        int l = L;
        while (l >= 0) {
            if (is_anc(up[l][i], j))
                l--;
            else
                i = up[l][i];
        }
        return up[0][i];
    }

    int semiget(int u, int d) {
        assert(is_anc(u, d));
        int l = L;
        while (l >= 0) {
            if (is_anc(up[l][d], u))
                l--;
            else
                d = up[l][d];
        }
        return d;
    }
};

St<ll> counts[2];
St<ll> depths[2];
Lca lca;
Hld<ll, Stl<ll>> hld[2];

int N;
vector<int> owner;
vector<set<int>> adj;
vector<int> parent;
vector<pair<int, int>> ranges;
vector<int> rawdepths;

void makeroot(int i) {
    for (int child : adj[i]) {
        adj[child].erase(i);
        parent[child] = i;
        makeroot(child);
    }
}

void setranges(int i, int& t) {
    int s = t;
    t += 1;
    for (int child : adj[i]) {
        setranges(child, t);
    }
    int e = t - 1;
    ranges[i] = {s, e};
}

void setdepths(int i, int d) {
    rawdepths[i] = d;
    for (int child : adj[i]) setdepths(child, d + 1);
}

pair<ll, ll> getdownraw(int l, int v) {
    ll d = depths[l].query(ranges[v].first, ranges[v].second);
    ll c = hld[l].query(v, v);
    // ll c = counts[l].query(ranges[v].first, ranges[v].second);
    return {d, c};
}

// get the total distance and amount of nodes belonging to a company in the
// subtree of a node, including that node.
pair<ll, ll> getdown(int l, int v) {
    auto d = getdownraw(l, v);
    d.first -= d.second * rawdepths[v];
    return d;
}

// get the total distance and amount of nodes belonging to a company in all of
// the connected nodes to a given node, excluding any nodes that are connected
// through the excluded child.
pair<ll, ll> getup(int l, int exchild) {
    auto rt = getdownraw(l, 0);
    auto ex = getdownraw(l, exchild);
    ll D = rawdepths[exchild];
    ll dd = rt.first - ex.first + (D + 1) * (rt.second + ex.second) -
            2 * hld[l].query(exchild, 0);
    ll cc = rt.second - ex.second;
    return {dd, cc};

    /*
    int updepth = 0;
    ll d = 0;
    ll c = 0;
    auto exclude = getdown(l, exchild);
    while (i != exchild) {
        auto full = getdown(l, i);
        ll dd = full.first - (exclude.first + exclude.second);
        ll cc = full.second - exclude.second;
        d += dd + cc * updepth;
        c += cc;

        // d += (dk - ck * (n - k)) - (de - ce * (n - (k - 1))) - ce +
        //     ck * (k - 1) - ce * (k - 1);
        // c += ck - ce;

        exclude = full;
        exchild = i;
        i = parent[i];
        updepth += 1;
    }
    return {d, c};
    */
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    owner.resize(N);
    adj.resize(N);
    parent.resize(N);
    ranges.resize(N);
    rawdepths.resize(N);
    rep(i, N) cin >> owner[i];
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].insert(v - 1);
        adj[v - 1].insert(u - 1);
    }

    lca = adj;
    rep(l, 2) hld[l] = Hld<ll, Stl<ll>>(adj, vector<ll>(N));
    rep(l, 2) rep(i, N) if (owner[i] == l) hld[l].update(i, 0, 1);
    makeroot(0);
    setdepths(0, 0);
    {
        int t = 0;
        setranges(0, t);
    }

    vector<ll> cs[2];
    vector<ll> dp[2];
    rep(l, 2) cs[l].resize(N);
    rep(l, 2) dp[l].resize(N);
    rep(i, N) {
        cs[owner[i]][ranges[i].first] = 1;
        dp[owner[i]][ranges[i].first] = rawdepths[i];
    }
    rep(l, 2) counts[l] = St<ll>(cs[l]);
    rep(l, 2) depths[l] = St<ll>(dp[l]);

    int Q;
    cin >> Q;
    rep(q, Q) {
        int op;
        cin >> op;
        if (op == 1) {
            // transaction
            int u;
            cin >> u;
            u -= 1;
            int p = ranges[u].first;
            int& o = owner[u];
            counts[o].update(p, 0);
            depths[o].update(p, 0);
            hld[o].update(u, 0, -1);
            o = !o;
            counts[o].update(p, 1);
            depths[o].update(p, rawdepths[u]);
            hld[o].update(u, 0, 1);
        } else if (op == 2) {
            // comparison
            int node[2];
            rep(k, 2) cin >> node[k];
            rep(k, 2) node[k] -= 1;
            int anc = lca.get(node[0], node[1]);
            if (anc == node[1]) swap(node[0], node[1]);
            pair<ll, ll> fracs[2][2];
            if (anc == node[0]) {
                // monke flip 2
                rep(l, 2) {
                    int exchild = lca.semiget(node[0], node[1]);
                    assert(parent[exchild] == node[0]);
                    fracs[l][0] = getup(l, exchild);
                    fracs[l][1] = getdown(l, node[1]);
                }
            } else {
                // monke flip
                rep(l, 2) rep(k, 2) fracs[l][k] = getdown(l, node[k]);
            }
            pair<ll, ll> cfracs[2];
            rep(l, 2) {
                cfracs[l] = {fracs[l][0].first * fracs[l][1].second +
                                 fracs[l][1].first * fracs[l][0].second,
                             fracs[l][0].second * fracs[l][1].second};
                if (cfracs[l].second == 0) cfracs[l].first = 1;
            }
            bigint a = cfracs[0].first;
            a *= cfracs[1].second;
            bigint b = cfracs[1].first;
            b *= cfracs[0].second;
            if (a < b)
                cout << "A\n";
            else if (a > b)
                cout << "B\n";
            else
                cout << "TIE\n";
        }
    }
}
