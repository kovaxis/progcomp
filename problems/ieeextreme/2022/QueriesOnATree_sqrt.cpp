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

template <class T>
struct Sparse {
    vector<vector<T>> st;

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
            max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))])); // query op
    }

    // query maximum in the range [l, r) in O(1) time
    T query(int l, int r) {
        int i = 31 - __builtin_clz(r - l);
        return max(st[i][l], st[i][r - (1 << i)]); // query op
    }
};

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

int N, Q;
vector<int> A, Atmp;

// arr[v] = sum_{w in V} A[w] * 2^-d(v, w)
vector<int> arr;

// S = sum_{v in V} A[v] * arr[v]
int S;

vector<vector<int>> G1;
vector<int> nodemap;
vector<int> adj, adjidx, parent;
int newn;
// A[q.first] += q.second
vector<pair<int, int>> qqueue;

vector<int> powhalf;

struct TreeDist {
    int n;
    vector<int> P;
    Sparse<int> H;

    TreeDist() {}

    void init() {
        P.resize(N);
        H.reset(2 * N);
        dfs(0, 0);
        H.init();
    }

    void dfs(int u, int d) {
        repx(j, adjidx[u], adjidx[u + 1]) {
            H.set(n++, -d);
            dfs(adj[j], d + 1);
        }
        P[u] = n, H.set(n++, -d);
    }

    // O(1)
    int dist(int u, int v) {
        u = P[u], v = P[v];
        if (u > v) swap(u, v);
        int ah = H.query(u, v + 1);
        return 2 * ah - H.st[0][u] - H.st[0][v];
    }
};

TreeDist dists;

int remap(int u, int p) {
    int nodei = newn++;
    int adji = adj.size();
    nodemap[u] = nodei;
    adjidx[nodei] = adji;
    adj.resize(adji + G1[u].size() - (p == -1 ? 0 : 1));
    for (int v : G1[u])
        if (v != p) {
            int childi = remap(v, u);
            adj[adji++] = childi;
            parent[childi] = nodei;
        }
    return nodei;
}

int dp_down(int u) {
    int x = A[u];
    repx(j, adjidx[u], adjidx[u + 1]) {
        int v = adj[j];
        x = (x + (ll)dp_down(v) * multinv(2)) % MOD;
    }
    return arr[u] = x;
}
void dp_up(int u) {
    if (parent[u] != -1) {
        arr[u] = (arr[u] + (ll)arr[parent[u]] * multinv(2) - (ll)arr[u] * multinv(4) % MOD + MOD) % MOD;
        // int up = sub(arr[parent[u]], mul(arr[u], multinv(2)));
        // arr[u] = add(arr[u], mul(up, multinv(2)));
    }
    repx(j, adjidx[u], adjidx[u + 1]) dp_up(adj[j]);
}
// O(N)
void calc_s() {
    dp_down(0);
    dp_up(0);
    S = 0;
    rep(u, N) S = (S + (ll)A[u] * arr[u]) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    A.resize(N);
    Atmp.resize(N);
    G1.assign(N, {});
    arr.resize(N);
    rep(i, N) cin >> Atmp[i];
    rep(j, N - 1) {
        int u, v;
        cin >> u >> v;
        G1[u - 1].push_back(v - 1);
        G1[v - 1].push_back(u - 1);
    }

    adjidx.resize(N + 1);
    nodemap.resize(N);
    parent.resize(N, -1);
    remap(0, -1);
    adjidx[N] = adj.size();

    rep(u, N) A[nodemap[u]] = Atmp[u];

    powhalf.resize(N + 1);
    powhalf[0] = 1;
    powhalf[1] = multinv(2);
    repx(i, 2, N + 1) powhalf[i] = mul(powhalf[i - 1], powhalf[1]);

    dists.init();
    calc_s();

    int rmult = binexp(2, N - 1);
    int B = sqrt(N) * 8;
    rep(qi, Q) {
        // recalculate S every B queries
        if (qqueue.size() >= B) {
            int old_s = S;
            calc_s();
            qqueue.clear();
            assert(old_s == S);
        }

        // read
        int u, k;
        cin >> u >> k;
        u = nodemap[u - 1];

        // set A[u] = k
        cerr << "setting A'[" << u << "] = " << k << " (A[u] is " << A[u] << ")" << endl;
        int delta = sub(k, A[u]);
        A[u] = k;

        // add to query queue
        qqueue.push_back({u, delta});

        // calculate arr'[u] taking into account all queries in the queue
        // arr'[v] = arr[v] + (A'[u] - A[u]) * 2^-d(v, u)
        int arr_u = arr[u];
        for (auto [q_u, q_d] : qqueue) {
            int change = mul(q_d, powhalf[dists.dist(q_u, u)]);
            arr_u = add(arr_u, change);
        }

        // adjust sum
        // S' = S + (A'[u] - A[u]) * (2*arr[u] + A'[u] - A[u])
        // S' = S + (A'[u] - A[u]) * (2*arr'[u] - (A'[u] - A[u]))
        cerr << "S' = S + (A'[u] - A[u]) * (2 * arr'[u] - (A'[u] - A[u])) = " << mul(rmult, S) << " + (" << delta << ") * (" << mul(rmult, mul(2, arr_u)) << " - " << mul(rmult, delta) << ")" << endl;
        S = add(S, mul(delta, sub(mul(2, arr_u), delta)));

        // print query result
        cout << mul(rmult, S) << "\n";
    }
}
