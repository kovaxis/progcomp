#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

template <class T>
struct St {
    int n;
    vector<T> a;

    T neut() { return {1e9, 0}; }
    T merge(T x, T y) { return min(x, y); }

    St(int n = 0) : n(n), a(2 * n, neut()) {}

    T query(int l, int r) {
        T x = neut(), y = neut();
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) x = merge(x, a[l++]);
            if (r & 1) y = merge(a[--r], y);
        }
        return merge(x, y);
    }

    void update(int i, T x) {
        for (a[i += n] = x; i /= 2;) a[i] = merge(a[2 * i], a[2 * i + 1]);
    }
};

struct Query {
    int qi;
    char ty;
    int v, l, k;
};

int N, M, T;
vector<vector<int>> G;
vector<Query> Q;
vector<int> L, R, D;
vector<int> ans;
St<pair<int, int>> nextquery;
vector<vector<int>> queriesat;

std::vector<int> prime;
bool is_composite[(int)1e6];
int phi[(int)1e6];

void sieve(int n) {
    std::fill(is_composite, is_composite + n, false);
    phi[1] = 1;
    for (int i = 2; i < n; ++i) {
        if (!is_composite[i]) {
            prime.push_back(i);
            phi[i] = i - 1; // i is prime
        }
        for (int j = 0; j < prime.size() && i * prime[j] < n; ++j) {
            is_composite[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j]; // prime[j] divides i
                break;
            } else {
                phi[i * prime[j]] = phi[i] * phi[prime[j]]; // prime[j] does not divide i
            }
        }
    }
}

void dfs(int u, int p) {
    L[u] = T++;
    for (int v : G[u])
        if (v != p) {
            D[v] = D[u] + 1;
            dfs(v, u);
        }
    R[u] = T;
}

// answer some query for a node at absolute depth d which was last updated by update query q
int answer(Query q, int d) {
    int x = q.l + d - D[q.v];
    return phi[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    sieve(1e6);

    cin >> N;
    G.resize(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    cin >> M;
    Q.resize(M);
    rep(qi, M) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int v, l, r;
            cin >> v >> l >> r;
            v--;
            Q[qi] = {qi, 'u', v, l, r - l};
        } else if (ty == 2) {
            int v;
            cin >> v;
            v--;
            Q[qi] = {qi, 'q', v};
        }
    }

    L.resize(N), R.resize(N), D.resize(N);
    dfs(0, -1);

    nextquery = {N};
    rep(i, N) nextquery.update(i, {1e9, i});
    queriesat.resize(N);

    ans.assign(M, -1);
    invrep(qi, M) {
        Query q = Q[qi];
        if (q.ty == 'q') {
            // query
            queriesat[L[q.v]].push_back(qi);
            nextquery.update(L[q.v], {D[q.v], L[q.v]});
        } else if (q.ty == 'u') {
            // update
            while (true) {
                // cerr << "getting next" << endl;
                auto [d, st_i] = nextquery.query(L[q.v], R[q.v]);
                if (d > D[q.v] + q.k) break;
                for (int qj : queriesat[st_i]) {
                    ans[qj] = answer(q, d);
                }
                nextquery.update(st_i, {1e9, st_i});
                queriesat[st_i].clear();
            }
        }
    }
    rep(i, N) for (int qi : queriesat[i]) {
        ans[qi] = 0;
    }

    rep(j, M) if (ans[j] != -1) cout << ans[j] << "\n";
}
