#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (ll i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

struct St {
    vector<int> a;

    St() {}
    St(int N) : a(4 * N, 0) {} // node neutral

    // query for range [l, r)
    int query(int l, int r, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (l <= vl && r >= vr) return a[v]; // item construction
        int vm = (vl + vr) / 2;
        if (l >= vr || r <= vl) return 0;                                   // item neutral
        return query(l, r, 2 * v, vl, vm) + query(l, r, 2 * v + 1, vm, vr); // item merge
    }

    // set element i to val
    void update(int i, int val, int v = 1, int vl = 0, int vr = -1) {
        if (vr == -1) vr = a.size() / 4;
        if (vr - vl == 1) a[v] = val; // item update
        else {
            int vm = (vl + vr) / 2;
            if (i < vm) update(i, val, 2 * v, vl, vm);
            else update(i, val, 2 * v + 1, vm, vr);
            a[v] = a[2 * v] + a[2 * v + 1]; // node merge
        }
    }
};

// build the suffix array
// suffixes are sorted, with each suffix represented by its starting position
vector<int> suffixarray(const string &s) {
    int N = s.size(); // + 1; // optional: include terminating NUL
    vector<int> p(N), p2(N), c(N), c2(N), cnt(256);
    rep(i, N) cnt[s[i]] += 1;
    repx(b, 1, 256) cnt[b] += cnt[b - 1];
    rep(i, N) p[--cnt[s[i]]] = i;
    repx(i, 1, N) c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
    for (int k = 1; k < N; k <<= 1) {
        int C = c[p[N - 1]] + 1;
        cnt.assign(C + 1, 0);
        for (int &pi : p) pi = (pi - k + N) % N;
        for (int cl : c) cnt[cl + 1] += 1;
        rep(i, C) cnt[i + 1] += cnt[i];
        rep(i, N) p2[cnt[c[p[i]]]++] = p[i];
        c2[p2[0]] = 0;
        repx(i, 1, N) c2[p2[i]] =
            c2[p2[i - 1]] + (c[p2[i]] != c[p2[i - 1]] ||
                             c[(p2[i] + k) % N] != c[(p2[i - 1] + k) % N]);
        swap(c, c2), swap(p, p2);
    }
    // p.erase(p.begin()); // optional: erase terminating NUL
    return p;
}

// build the lcp
// `lcp[i]` represents the length of the longest common prefix between suffix i
// and suffix i+1 in the suffix array `p`. the last element of `lcp` is zero by
// convention
vector<int> makelcp(const string &s, const vector<int> &p) {
    int N = p.size(), k = 0;
    vector<int> r(N), lcp(N);
    rep(i, N) r[p[i]] = i;
    rep(i, N) {
        if (r[i] + 1 >= N) {
            k = 0;
            continue;
        }
        int j = p[r[i] + 1];
        while (i + k < N && j + k < N && s[i + k] == s[j + k]) k += 1;
        lcp[r[i]] = k;
        if (k) k -= 1;
    }
    return lcp;
}

template <class T>
struct Sparse {
    vector<vector<T>> st;

    T op(T a, T b) { return min(a, b); }

    Sparse() {}

    void reset(int N) { st = {vector<T>(N)}; }
    void set(int i, T val) { st[0][i] = val; }

    // O(N log N) time
    // O(N log N) memory
    void init() {
        int N = st[0].size();
        int npot = N <= 1 ? 1 : 32 - __builtin_clz(N);
        st.resize(npot);
        repx(i, 1, npot) rep(j, N + 1 - (1 << i)) st[i].push_back(
            op(st[i - 1][j], st[i - 1][j + (1 << (i - 1))])); // query op
    }

    // query maximum in the range [l, r) in O(1) time
    // range must be nonempty!
    T query(int l, int r) {
        int i = 31 - __builtin_clz(r - l);
        return op(st[i][l], st[i][r - (1 << i)]); // query op
    }
};

// find the range of suffix-array indices that share a common prefix of at least K
// with the suffix at index i
// O(log N)
pair<int, int> lcprange(Sparse<int> &lcp, int i, int K) {
    int N = lcp.st[0].size(), l = 0, r = i, lo;
    while (l != r) {
        int m = (l + r) / 2;
        if (lcp.query(m, i) >= K) r = m;
        else l = m + 1;
    }
    lo = l, l = i, r = N - 1;
    while (l != r) {
        int m = (l + r + 1) / 2;
        if (lcp.query(i, m)) l = m;
        else r = m - 1;
    }
    return {lo, r + 1};
}

// lexicographically compare the suffixes starting from `i` and `j`,
// considering only up to `K` characters.
// `r` is the inverse suffix array, mapping suffix offsets to indices.
int lcp_cmp(vector<int> &r, Sparse<int> &lcp, int i, int j, int K) {
    if (i == j) return 0;
    int ii = r[i], jj = r[j];
    int l = lcp.query(min(ii, jj), max(ii, jj));
    if (l >= K) return 0;
    return ii < jj ? -1 : 1;
}

struct Edge {
    int v;
    char c;
};

struct Hld {
    vector<int> P, H, D, pos, top;
    string PC;

    Hld() {}
    void init(vector<vector<Edge>> &G) {
        int N = G.size();
        P.resize(N), H.resize(N), D.resize(N), pos.resize(N),
            top.resize(N), PC.resize(N);
        D[0] = -1, dfs(G, 0);
        int t = 0;
        rep(i, N) if (H[P[i]] != i) {
            int j = i;
            while (j != -1) {
                top[j] = i, pos[j] = t++;
                j = H[j];
            }
        }
    }

    int dfs(vector<vector<Edge>> &G, int i) {
        int w = 1, mw = 0;
        D[i] = D[P[i]] + 1, H[i] = -1;
        for (Edge e : G[i]) {
            int c = e.v;
            if (c == P[i]) continue;
            P[c] = i;
            PC[c] = e.c;
            int sw = dfs(G, c);
            if (sw > mw) H[i] = c, mw = sw;
            w += sw;
        }
        return w;
    }

    template <class OP>
    void path(int u, int v, OP op) {
        cerr << "path from " << u + 1 << " to " << v + 1 << endl;

        int lu = u, lv = v;
        while (top[lu] != top[lv]) {
            if (D[top[lu]] > D[top[lv]]) lu = P[top[lu]];
            else lv = P[top[lv]];
        }
        int lca = D[lu] > D[lv] ? lv : lu;

        cerr << "lca is " << lca + 1 << endl;

        while (top[u] != top[lca]) {
            op(pos[top[u]], pos[u] + 1, false);
            u = P[top[u]];
        }

        if (u != lca)
            op(pos[lca] + 1, pos[u] + 1, false);

        vector<int> stk;
        while (top[v] != top[lca])
            stk.push_back(v), v = P[top[v]];

        // op(pos[lca], pos[v] + 1, true);  // value on vertex
        op(pos[lca] + 1, pos[v] + 1, true); // value on edge
        reverse(stk.begin(), stk.end());
        for (int w : stk)
            op(pos[top[w]], pos[w] + 1, true);
    }
};

struct Query {
    int u, v, l, r;
    int sa_lo, sa_hi;
    int ans = 0;
};

int N, M, Q;
vector<vector<Edge>> G;
vector<string> S;
vector<Query> queries;

Hld hld;
vector<int> sa, invsa, lcp_arr, Smap;
int hldmap, hldinvmap;
Sparse<int> lcp;
St active;
vector<vector<int>> checkquery;

pair<int, int> hone(int Lo, int Hi, int shift, int ref, int reflen) {
    int l = Lo, r = Hi, lo;
    while (l != r) {
        int m = (l + r) / 2;
        if (lcp_cmp(invsa, lcp, sa[m] + shift, ref, reflen) >= 0) r = m;
        else l = m + 1;
    }
    lo = l, r = Hi;
    while (l != r) {
        int m = (l + r) / 2;
        if (lcp_cmp(invsa, lcp, sa[m] + shift, ref, reflen) > 0) r = m;
        else l = m + 1;
    }
    return {lo, r};
}

int main() {
    cin >> N >> M >> Q;
    G.resize(N);
    rep(j, N - 1) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        u--, v--;
        G[u].push_back({v, c});
        G[v].push_back({u, c});
    }
    S.resize(M);
    rep(j, M) cin >> S[j];
    queries.resize(Q);
    rep(q, Q) {
        int u, v, l, r;
        cin >> u >> v >> l >> r;
        u--, v--, l--;
        queries[q] = {u, v, l, r};
    }

    cerr << "read input" << endl;

    hld.init(G);
    string flat(N, ' ');
    rep(u, N) {
        flat[hld.pos[u]] = hld.PC[u];
    }

    cerr << "built hld: " << flat << endl;

    string all;
    for (string &s : S) Smap.push_back(all.size()), all.append(s.begin(), s.end()), all.push_back('!');
    hldmap = all.size();
    all.append(flat.begin(), flat.end());
    all.append(flat.rbegin(), flat.rend());
    hldinvmap = all.size();
    all.push_back('!');

    sa = suffixarray(all);
    invsa.resize(sa.size());
    rep(i, sa.size()) invsa[sa[i]] = i;

    lcp_arr = makelcp(all, sa);
    lcp.reset(lcp_arr.size());
    rep(i, lcp_arr.size()) lcp.set(i, lcp_arr[i]);
    lcp.init();

    cerr << "built suffix array: " << all << endl;

    rep(qi, Q) {
        auto &q = queries[qi];
        cerr << "processing query " << qi + 1 << " on nodes " << q.u + 1 << " -> " << q.v + 1 << " and range [" << q.l + 1 << ", " << q.r << "]" << endl;
        int Lo = 0, Hi = sa.size();
        int prefix = 0;
        hld.path(q.u, q.v, [&](int ir, int jr, bool fw) {
            int i = fw ? hldmap + ir : hldinvmap - jr;
            int j = fw ? hldmap + jr : hldinvmap - ir;
            if (i >= j) return;

            cerr << "processing hld segment " << flat.substr(ir, jr - ir) << " -> " << all.substr(i, j - i) << endl;

            int len = j - i;
            auto [lo, hi] = hone(Lo, Hi, prefix, i, len);
            cerr << "reduced suffix-array range to [" << lo + 1 << ", " << hi << "]" << endl;

            Lo = lo, Hi = hi, prefix += len;
        });

        cerr << "query is on suffix-array range [" << Lo + 1 << ", " << Hi << "]" << endl;
        q.sa_lo = Lo, q.sa_hi = Hi;
    }

    checkquery.resize(M + 1);
    rep(qi, Q) {
        auto &q = queries[qi];
        checkquery[q.l].push_back(qi);
        if (q.r != q.l) checkquery[q.r].push_back(qi);
    }

    active = {(int)sa.size()};
    rep(j, M + 1) {
        for (int qi : checkquery[j]) {
            auto &q = queries[qi];
            if (q.l == j) {
                cerr << "checking start of query " << qi + 1 << " before adding word " << j + 1 << endl;
                q.ans -= active.query(q.sa_lo, q.sa_hi);
            }
            if (q.r == j) {
                cerr << "checking end of query " << qi + 1 << " after adding word " << j << endl;
                q.ans += active.query(q.sa_lo, q.sa_hi);
            }
        }

        if (j < M)
            rep(i, S[j].size()) active.update(invsa[Smap[j] + i], 1);
    }

    for (auto &q : queries) cout << q.ans << "\n";
}
