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

template <class T>
struct st {
    vector<T> node;

    st() {}
    st(vector<T> a) { build(a); }

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

// calculates the lowest common ancestor for any two nodes in O(log N) time,
// with O(N log N) preprocessing
struct lca {
    int L;
    vector<vector<int>> up;
    vector<pair<int, int>> time;

    lca() {}
    lca(const vector<set<int>>& adj) {
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
};

st<ll> counts[2];
st<ll> depths[2];
lca lcanc;

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

pair<ll, ll> traverseup(int l, int i, int exchild) {
    int updepth = 0;
    ll ds = 0;
    ll cs = 0;
    while (parent[i] != i) {
        ds += depths[l].query(ranges[i].first, ranges[i].first);
        cs += counts[l].query(ranges[i].first, ranges[i].first);
        for (int child : adj[i]) {
            if (child == exchild) continue;
            ll vdists =
                depths[l].query(ranges[child].first, ranges[child].second);
            ll vcounts =
                counts[l].query(ranges[child].first, ranges[child].second);
            vdists += vcounts * (updepth - rawdepths[i]);
            ds += vdists;
            cs += vcounts;
        }
        exchild = i;
        i = parent[i];
        updepth += 1;
    }
    return {ds, cs};
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

    lcanc = lca(adj);
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
    rep(l, 2) counts[l] = st<ll>(cs[l]);
    rep(l, 2) depths[l] = st<ll>(dp[l]);

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
            counts[owner[u]].update(p, 0);
            depths[owner[u]].update(p, 0);
            owner[u] = !owner[u];
            counts[owner[u]].update(p, 1);
            depths[owner[u]].update(p, rawdepths[u]);
        } else if (op == 2) {
            // comparison
            int u, v;
            cin >> u >> v;
            u -= 1;
            v -= 1;
            int anc = lcanc.get(u, v);
            if (anc == v) swap(u, v);
            pair<ll, ll> fracs[2];
            if (anc == u) {
                // trick does not work
                rep(l, 2) {
                    int goodchild;
                    for (int child : adj[u]) {
                        if (lcanc.is_anc(child, v)) goodchild = child;
                    }
                    auto upfrac = traverseup(l, u, goodchild);
                    ll udists = upfrac.first;
                    ll ucounts = upfrac.second;
                    if (ucounts == 0) udists = 1;

                    ll vdists =
                        depths[l].query(ranges[v].first, ranges[v].second);
                    ll vcounts =
                        counts[l].query(ranges[v].first, ranges[v].second);
                    vdists -= vcounts * rawdepths[anc];
                    if (vcounts == 0) vdists = 1;

                    fracs[l] = {udists * vcounts + vdists * ucounts,
                                ucounts * vcounts};
                    if (fracs[l].second == 0) fracs[l].first = 1;
                }
            } else {
                // monke flip
                rep(l, 2) {
                    ll udists =
                        depths[l].query(ranges[u].first, ranges[u].second);
                    ll ucounts =
                        counts[l].query(ranges[u].first, ranges[u].second);
                    udists -= ucounts * rawdepths[anc];
                    if (ucounts == 0) udists = 1;

                    ll vdists =
                        depths[l].query(ranges[v].first, ranges[v].second);
                    ll vcounts =
                        counts[l].query(ranges[v].first, ranges[v].second);
                    vdists -= vcounts * rawdepths[anc];
                    if (vcounts == 0) vdists = 1;

                    fracs[l] = {udists * vcounts + vdists * ucounts,
                                ucounts * vcounts};
                    if (fracs[l].second == 0) fracs[l].first = 1;
                }
            }
            int a = fracs[0].first * fracs[1].second;
            int b = fracs[1].first * fracs[0].second;
            if (a < b)
                cout << "A\n";
            else if (a > b)
                cout << "B\n";
            else
                cout << "TIE\n";
        }
    }
}
