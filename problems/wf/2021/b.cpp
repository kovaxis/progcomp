#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Edge {
    int v;
    ll w;
};

struct Lca {
    int N, K, t = 0;
    vector<vector<int>> U;
    vector<int> L, R;

    Lca() {}
    Lca(vector<vector<Edge>> &G, int R) : N(G.size()), L(N), R(N) {
        K = N <= 1 ? 0 : 32 - __builtin_clz(N - 1);
        U.assign(K + 1, vector<int>(N));
        visit(G, R, R);
        rep(k, K) rep(u, N) U[k + 1][u] = U[k][U[k][u]];
    }

    void visit(vector<vector<Edge>> &G, int u, int p) {
        L[u] = t++, U[0][u] = p;
        for (Edge e : G[u])
            if (e.v != p) visit(G, e.v, u);
        R[u] = t++;
    }

    bool is_anc(int up, int dn) {
        return L[up] <= L[dn] && R[dn] <= R[up];
    }

    int find(int u, int v) {
        if (is_anc(u, v)) return u;
        if (is_anc(v, u)) return v;
        for (int k = K; k >= 0;)
            if (is_anc(U[k][u], v)) k--;
            else u = U[k][u];
        return U[0][u];
    }

    int almost_reach(int u, int v) {
        assert(is_anc(v, u) && u != v);
        for (int k = K; k >= 0;)
            if (is_anc(U[k][u], v)) k--;
            else u = U[k][u];
        assert(U[0][u] == v);
        return u;
    }
};

struct Hld {
    vector<int> P, H, D, pos, top;

    Hld() {}
    void init(vector<vector<Edge>> &G, int root) {
        int N = G.size();
        P.assign(N, 0), H.assign(N, 0), D.assign(N, 0), pos.assign(N, 0),
            top.assign(N, 0);
        P[root] = root;
        D[root] = -1, dfs(G, root);
        int t = 0;
        rep(i, N) if (H[P[i]] != i) {
            for (int j = i; j != -1; j = H[j])
                top[j] = i, pos[j] = t++;
        }
    }

    int dfs(vector<vector<Edge>> &G, int i) {
        int w = 1, mw = 0;
        D[i] = D[P[i]] + 1, H[i] = -1;
        for (Edge e : G[i]) {
            if (e.v == P[i]) continue;
            P[e.v] = i;
            int sw = dfs(G, e.v);
            if (sw > mw) H[i] = e.v, mw = sw;
            w += sw;
        }
        return w;
    }

    // visit the log N segments in the path from u to v
    template <class OP>
    void path(int u, int v, OP op) {
        while (top[u] != top[v]) {
            if (D[top[u]] > D[top[v]]) swap(u, v);
            op(pos[top[v]], pos[v] + 1);
            v = P[top[v]];
        }
        if (D[u] > D[v]) swap(u, v);
        // op(pos[u], pos[v] + 1); // value on vertex
        op(pos[u] + 1, pos[v] + 1); // value on path
    }

    // commutative (lazy) segment tree
    template <class T, class S>
    T query(S &seg, int u, int v) {
        T ans = 1e18; // neutral element
        path(u, v, [&](int l, int r) {
            if (l == r) return;
            ans = min(ans, seg.query(l, r));
        }); // query op
        return ans;
    }
};

template <class T>
struct Sparse {
    vector<vector<T>> st;

    T op(T a, T b) { return min(a, b); }

    Sparse() {}
    Sparse(int N) : st{vector<T>(N)} {}

    T &operator[](int i) { return st[0][i]; }

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

struct Query {
    int q;
    int R, K, T;
};

int N, Q, R;
vector<vector<Edge>> G;
vector<ll> P, H1, H2;
ll S;

Lca lca;
Hld hld;
Sparse<ll> B, F;

void accum_p(int u, int p) {
    for (Edge e : G[u])
        if (e.v != p) {
            P[e.v] = P[u] + e.w;
            accum_p(e.v, u);
        }
}

void find_hang(int u, int p) {
    H1[u] = P[u], H2[u] = 0;
    for (Edge e : G[u])
        if (e.v != p) {
            find_hang(e.v, u);
            if (H1[e.v] >= H1[u]) {
                H2[u] = H1[u];
                H1[u] = H1[e.v];
            } else if (H1[e.v] >= H2[u]) {
                H2[u] = H1[e.v];
            }
        }
}

ll hang(int u) {
    return H1[u];
}

ll hang_not(int u, int exclude) {
    return H1[u] == H1[exclude] ? H2[u] : H1[u];
}

void prepare() {
    // cerr << "rooting from " << R + 1 << endl;

    lca = {G, R};

    P.assign(N, 0);
    accum_p(R, R);

    H1.assign(N, 0), H2.assign(N, 0);
    find_hang(R, R);

    S = 0;
    rep(u, N) for (Edge e : G[u]) S += e.w;
    S /= 2;

    hld.init(G, R);

    B = {N};
    rep(u, N) {
        B[hld.pos[u]] = 2 * P[hld.P[u]] - hang_not(hld.P[u], u);
    }
    B.init();

    F = {N};
    rep(u, N) {
        F[hld.pos[u]] = -hang_not(hld.P[u], u);
    }
    F.init();

    // rep(u, N) {
    //     cerr << "PATH[" << u + 1 << "] = " << P[u] << endl;
    // }
    // cerr << endl;
    // rep(u, N) {
    //     cerr << "HANG[" << u + 1 << "] = " << hang(u) << endl;
    // }
    // cerr << endl;
    // rep(u, N) {
    //     cerr << "HANGNOT[" << hld.P[u] + 1 << "][" << u + 1 << "] = " << hang_not(hld.P[u], u) << endl;
    // }
    // cerr << endl;
}

ll solve(int K, int T) {
    int L = lca.find(K, T);
    if (L == T) return -1;
    if (L == K) return 2 * S - hang(R);
    // end in subtree of K
    ll under_k = 2 * S - hang(K) + 2 * (P[K] - P[L]);
    // end outside substree of Kup
    int Kup = lca.almost_reach(K, L);
    ll outside_kup = 2 * S + hld.query<ll, Sparse<ll>>(F, R, Kup);
    // end in the subtree of Kup but not in the subtree of K
    ll between_kup_and_k = 2 * S + hld.query<ll, Sparse<ll>>(B, Kup, K) - 2 * P[L];

    ll ans = min(under_k, min(outside_kup, between_kup_and_k));
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    G.resize(N);
    rep(j, N - 1) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }

    vector<Query> qs(Q);
    rep(q, Q) {
        int R, K, T;
        cin >> R >> K >> T;
        R--, K--, T--;
        qs[q] = {q, R, K, T};
    }

    sort(qs.begin(), qs.end(), [](Query a, Query b) {
        return a.R < b.R;
    });

    R = -1;
    vector<ll> ans(Q);
    for (Query &q : qs) {
        if (R != q.R) {
            R = q.R;
            prepare();
        }
        ans[q.q] = solve(q.K, q.T);
    }

    for (ll y : ans) {
        if (y == -1) {
            cout << "impossible\n";
        } else {
            cout << y << "\n";
        }
    }
}
