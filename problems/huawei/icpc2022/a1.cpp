#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

// hackproof rng
static mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// hackproof unordered map hash
struct Hash {
    size_t operator()(const ll &x) const {
        static const uint64_t RAND =
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t z = x + RAND + 0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        return z ^ (z >> 31);
    }
};

// hackproof unordered_map
template <class T, class U>
using umap = unordered_map<T, U, Hash>;

// hackproof unordered_set
template <class T>
using uset = unordered_set<T, Hash>;

struct Dsu {
    int comp_cnt;
    vector<int> p, r, sz;

    Dsu() {}
    Dsu(int N) { reset(N); }

    // initialize the disjoint-set-union to all unitary sets
    void reset(int N) {
        comp_cnt = N;
        p.resize(N), r.assign(N, 0), sz.assign(N, 1);
        rep(i, N) p[i] = i;
    }

    // find the leader node corresponding to node `i`
    int find(int i) {
        if (p[i] != i) p[i] = find(p[i]);
        return p[i];
    }

    // perform union on the two sets of `i` and `j`
    void unite(int i, int j) {
        i = find(i), j = find(j);
        if (i == j) return;
        if (r[i] > r[j]) swap(i, j);
        if (r[i] == r[j]) r[j] += 1;
        sz[j] += sz[i];
        comp_cnt -= 1;
        p[i] = j;
    }
};

int N, M;
vector<vector<pair<ll, int>>> G;
vector<pair<ll, pair<int, int>>> E;

pair<int, vector<vector<int>>> dsu2part(Dsu &dsu) {
    umap<int, vector<int>> Pmap;
    rep(i, N) Pmap[dsu.find(i)].push_back(i);

    vector<vector<int>> P(Pmap.size());
    int j = 0;
    for (auto &[i, p] : Pmap) swap(P[j++], p);

    int mx_p = 0;
    for (auto &p : P) mx_p = max(mx_p, (int)p.size());

    int score = P.size() + mx_p - 1;
    return {score, P};
}

int dsu_score(Dsu &dsu) {
    int mx_p = 0;
    rep(i, N) mx_p = max(mx_p, dsu.sz[i]);
    return dsu.comp_cnt + mx_p - 1;
}

pair<int, vector<vector<int>>> sorted_edges_greedy() {
    int B = ceil(sqrt(N));
    int mx_sz = 0;

    Dsu dsu;
    dsu.reset(N);

    while (dsu.comp_cnt > mx_sz) {
        for (auto [w, uv] : E) {
            auto [u, v] = uv;
            u = dsu.find(u), v = dsu.find(v);
            if (u != v && dsu.sz[u] + dsu.sz[v] > B) continue;
            dsu.unite(u, v);
            mx_sz = max(mx_sz, dsu.sz[dsu.find(u)]);
        }

        // cerr << "iteration with partition limit " << B << ":" << endl;
        //  report(dsu, false);

        B = max(B, mx_sz) + 1;
    }

    return dsu2part(dsu);
}

pair<int, vector<vector<int>>> small_to_large() {
    vector<vector<int>> G2(N);
    rep(u, N) for (auto [w, v] : G[u]) G2[u].push_back(v);

    vector<int> choose_buf;

    int B = ceil(sqrt(N));

    Dsu dsu;
    dsu.reset(N);

    // randomize indices
    vector<int> obf(N), deobf(N);
    rep(i, N) obf[i] = i;
    shuffle(obf.begin(), obf.end(), rng);
    rep(i, N) deobf[obf[i]] = i;

    // {{-group_size, -adjacent_edges}, obfuscated_index}
    priority_queue<pair<pair<int, int>, int>> q;
    rep(i, N) q.push({{-1, -G2[deobf[i]].size()}, i});

    while (!q.empty()) {
        auto [szadj, idx] = q.top();
        auto [sz, adj] = szadj;
        sz = -sz, adj = -adj;
        int u = deobf[idx];
        q.pop();

        u = dsu.find(u);
        if (dsu.sz[u] != sz) continue;

        // choose the smallest group to join with
        if (G2[u].empty()) continue;
        int mn_sz = 1e9;
        choose_buf.clear();
        // cerr << "choosing edge for vertex with " << G2[u].size() << " edges" << endl;
        for (int maybe_v : G2[u]) {
            // cerr << "    edge to " << maybe_v << endl;
            maybe_v = dsu.find(maybe_v);
            int v_sz = dsu.sz[maybe_v];
            // cerr << "  edge leads to group " << maybe_v << " with " << v_sz << " vertices" << endl;
            if (v_sz < mn_sz) mn_sz = v_sz, choose_buf.clear();
            if (v_sz <= mn_sz) choose_buf.push_back(maybe_v);
        }
        int v;
        {
            uniform_int_distribution<> distr(0, choose_buf.size() - 1);
            v = choose_buf[distr(rng)];
        }

        // join both groups
        if (dsu.sz[u] + dsu.sz[v] > 2 * B) {
            cerr << "skipping join of group with size " << dsu.sz[u] << " and size " << dsu.sz[v] << endl;
            continue;
        }
        // cerr << "joining group with size " << dsu.sz[u] << " and size " << dsu.sz[v] << endl;
        dsu.unite(u, v);
        int lead = dsu.find(u);
        int nonlead = lead == u ? v : u;

        // fix G2 by joining edges from u and v, but skipping edges that join both
        uset<int> new_adj;
        new_adj.reserve(G2[u].size() + G2[v].size());
        for (int other : G2[lead]) new_adj.insert(dsu.find(other));
        new_adj.erase(lead);
        G2[lead].clear();
        G2[lead].reserve(new_adj.size());
        for (int other : new_adj) G2[lead].push_back(other);

        // add new merged group to priority queue
        q.push({{-dsu.sz[lead], -G2[lead].size()}, obf[lead]});
    }

    return dsu2part(dsu);
}

void check_integrity(const vector<vector<int>> &P) {

    uset<int> allset;
    allset.reserve(N);
    for (auto &p : P) {
        if (p.empty()) {
            cerr << "empty partition found" << endl;
            exit(1);
        }
        for (int u : p) {
            if (u < 0 || u >= N) {
                cerr << "invalid vertex id " << u << endl;
                exit(1);
            }
            if (allset.count(u)) {
                cerr << "vertex " << u << " is duplicated in partitioning" << endl;
                exit(1);
            }
            allset.insert(u);
        }
    }
    if (allset.size() != N) {
        cerr << "partitions do not cover all vertices" << endl;
        exit(1);
    }

    vector<uset<int>> Pset(P.size());
    rep(i, P.size()) for (int u : P[i]) Pset[i].insert(u);
}

void report(const vector<vector<int>> &P, bool distr) {
    int B = ceil(sqrt(N));
    int Q = (N + B - 1) / B;
    cerr << "  ideal partitioning: " << B << " partitions with at most " << Q << " nodes" << endl;

    map<int, int> sz_distr;
    int mx_p = 0;
    for (auto &p : P) {
        mx_p = max(mx_p, (int)p.size());
        sz_distr[p.size()] += 1;
    }
    cerr << "  " << P.size() << " partitions" << endl;
    cerr << "  maximum partition size: " << mx_p << endl;
    cerr << "  actual score: " << P.size() + mx_p - 1 << endl;
    cerr << "  ideal score: " << B + Q - 1 << endl;
    if (distr) {
        cerr << "  partition sizes:" << endl;
        for (auto [sz, cnt] : sz_distr) cerr << "    " << sz << " nodes: " << cnt << " partitions" << endl;
    }
}

void check_part(const char *name, int &mx_score, vector<vector<int>> &mx_P, pair<int, vector<vector<int>>> sP) {
    auto &[s, P] = sP;
    cerr << name << ":" << endl;
    report(P, false);
    if (s < mx_score) mx_score = s, mx_P = P;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    G.resize(N);
    rep(j, M) {
        ll u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({w, v});
        G[v].push_back({w, u});
        E.push_back({w, {u, v}});
    }

    cerr << N << " nodes, " << M << " edges" << endl;

    sort(E.begin(), E.end());

    int score = 1e9;
    vector<vector<int>> P;
    check_part("sorted_edges_greedy", score, P, sorted_edges_greedy());
    check_part("small_to_large", score, P, small_to_large());

    cerr << "final result:" << endl;
    report(P, true);

    for (auto &p : P) {
        cout << p.size();
        for (int u : p) cout << " " << u;
        cout << "\n";
    }
}
