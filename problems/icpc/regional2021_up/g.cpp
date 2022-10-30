#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

// hackproof unordered map hash
struct uHash {
    size_t operator()(const ll& x) const {
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
using umap = unordered_map<T, U, uHash>;

// hackproof unordered_set
template <class T>
using uset = unordered_set<T, uHash>;

const ll INF = 1e18;

struct Tree {
    int i, k;
    vector<vector<int>> g;
};

ll M[2] = {1000003931, 1000000007};
static const ll P[2] = {
    chrono::steady_clock::now().time_since_epoch().count() % (1 << 29),
    (chrono::steady_clock::now().time_since_epoch().count() + 1284729) %
        (1 << 29)};
vector<ll> p[2];

int N;
vector<Tree> trees;
vector<int> equiv;
vector<int> ecount;
umap<ll, int> known;
vector<int> ans;

struct Hash {
    int l;
    int h[2];

    Hash() : l(0), h{0, 0} {}
    Hash(int v) : l(1) { rep(k, 2) h[k] = (ll)v * P[k] % M[k]; }

    void append(Hash sh) {
        rep(k, 2) h[k] = (h[k] + (ll)sh.h[k] * p[k][l] % M[k]) % M[k];
        l += sh.l;
    }

    ll sum() { return (ll)h[0] | (((ll)h[1]) << 32); }
};

struct Hasher {
    int K;
    vector<vector<int>>& G;
    vector<umap<int, Hash>> dpmem;
    umap<int, int> found;

    Hasher(Tree& t) : K(t.k), G(t.g) { dpmem.resize(K); }

    Hash dp(int u, int j) {
        if (dpmem[u].count(j)) return dpmem[u][j];

        // cerr << "visiting node " << u << endl;
        vector<Hash> sub;
        for (int v : G[u]) {
            if (v == j) continue;
            // cerr << "  checking neighbor " << v << endl;
            sub.push_back(dp(v, u));
        }
        sort(sub.begin(), sub.end(), [](Hash& a, Hash& b) {
            if (a.l != b.l) return a.l < b.l;
            if (a.h[0] != b.h[0]) return a.h[0] < b.h[0];
            return a.h[1] < b.h[1];
        });
        Hash h;
        h.append(Hash(1));
        for (Hash sh : sub) h.append(sh);
        h.append(Hash(2));

        ll hsm = h.sum();
        if (known.count(hsm)) {
            int i = known[hsm], subk = trees[i].k;
            if (K % subk == 0) found[subk] = i;
        }
        return dpmem[u][j] = h;
    }

    ll hash(int u, int j = -1) { return dp(u, j).sum(); }
};

struct Decompose {
    int K;
    vector<vector<int>>& G;
    int subi;

    Hash visit(int u, int j = -1) {
        // cerr << "      visiting node " << u << endl;
        vector<Hash> sub;
        // cerr << "      visiting neighbors" << endl;
        for (int v : G[u]) {
            // cerr << "      maybe visit neighbor " << v << "?" << endl;
            if (v == j) continue;
            // cerr << "      visiting neighbor " << v << endl;
            sub.push_back(visit(v, u));
            // cerr << "      visited neighbor " << v << " and got {" <<
            // subh.first
            //     << ", " << subh.second << "}" << endl;
        }
        sort(sub.begin(), sub.end(), [](Hash& a, Hash& b) {
            if (a.l != b.l) return a.l < b.l;
            if (a.h[0] != b.h[0]) return a.h[0] < b.h[0];
            return a.h[1] < b.h[1];
        });
        Hash h;
        h.append(Hash(1));
        for (Hash sh : sub) h.append(sh);
        h.append(Hash(2));

        ll hsm = h.sum();
        if (known.count(hsm) && known[hsm] == subi) h = Hash();
        return h;
    }

    Decompose(Hasher& h, int i) : K(h.K), G(h.G), subi(i) {}
};

void process(Tree& t) {
    // cerr << "processing tree " << t.i << endl;
    Hasher h(t);
    // cerr << "  built hasher" << endl;
    if (known.count(h.hash(0))) {
        // cerr << "  equivalent" << endl;
        equiv[t.i] = known[h.hash(0)];
        ans[equiv[t.i]] += 1;
        ecount[equiv[t.i]] += 1;
        return;
    }
    // cerr << "  checked equivalence" << endl;

    rep(u, t.k) h.hash(u);
    // cerr << "  built all hashes, found " << h.found.size()
    //     << " potential subtrees" << endl;
    for (auto [subk, subi] : h.found) {
        // cerr << "  checking subbuild with tree " << subi << endl;
        Decompose dec(h, subi);
        // cerr << "    built decomposer" << endl;
        Hash fh = dec.visit(0);
        // cerr << "    finished visiting with hash " << fh.second
        //     << " and length " << fh.first << endl;
        if (fh.l == 0) ans[t.i] += ecount[subi];
    }

    rep(u, t.k) known[h.hash(u)] = t.i;
    // cerr << "added hashes to known hashes" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    rep(k, 2) {
        p[k].resize((int)5e5);
        p[k][0] = 1;
        repx(i, 1, (int)5e5) p[k][i] = (ll)p[k][i - 1] * P[k] % M[k];
    }

    cin >> N;
    trees.resize(N);
    rep(i, N) {
        Tree& t = trees[i];
        t.i = i;
        cin >> t.k;
        t.g.resize(t.k);
        rep(j, t.k - 1) {
            int u, v;
            cin >> u >> v;
            t.g[u - 1].push_back(v - 1);
            t.g[v - 1].push_back(u - 1);
        }
    }

    cerr << "read input" << endl;

    ans.resize(N);
    equiv.resize(N);
    rep(i, N) equiv[i] = i;
    ecount.assign(N, 1);

    cerr << "built equiv" << endl;

    vector<Tree*> tsort(N);
    rep(i, N) tsort[i] = &trees[i];
    sort(tsort.begin(), tsort.end(),
         [](Tree* a, Tree* b) { return a->k < b->k; });

    cerr << "sorted trees" << endl;

    for (Tree* t : tsort) process(*t);

    cerr << "processed trees" << endl;

    rep(i, N) cout << ans[equiv[i]] << " \n"[i == N - 1];
}
