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

const ll MOD = 527944876156977883ll;
static vector<ll> P;

struct Tree {
    int size;
    vector<Tree> children;
};

int N;
vector<vector<int>> G;
uset<ll> PG;
vector<umap<ll, Tree>> all;
vector<int> distr;
Tree ans;
int next_id;
vector<pair<int, int>> E;

pair<ll, int> hashtree(int u, int p) {
    vector<pair<ll, int>> sh;
    for (int v : G[u])
        if (v != p) {
            sh.push_back(hashtree(v, u));
        }
    sort(sh.begin(), sh.end());
    ll h = 1;
    int L = 1;
    for (auto [hh, l] : sh) h = ((__int128)h * P[l] + hh) % MOD, L += l;
    h = ((__int128)h * P[1] + 2) % MOD;
    L += 1;
    PG.insert(h);
    return {h, L};
}

bool visit_all_in_distr(int size) {
    int N = distr.size();
    rep(i, distr.size()) if (distr[i] == 0) {
        N = i;
        break;
    }

    cerr << "visiting distribution";
    rep(i, N) cerr << " " << distr[i];
    cerr << endl;

    vector<umap<ll, Tree>::iterator> iters;
    rep(i, N) iters.push_back(all[distr[i]].begin());
    vector<pair<ll, int>> sh(N);
    while (true) {
        rep(i, N) sh[i] = {iters[i]->first, iters[i]->second.size};
        sort(sh.begin(), sh.end());
        ll h = 1;
        int L = 1;
        for (auto [hh, l] : sh) h = ((__int128)h * P[l] + hh) % MOD, L += l;
        h = ((__int128)h * P[1] + 2) % MOD;
        L += 1;

        Tree tree;
        tree.size = L;
        rep(i, N) tree.children.push_back(iters[i]->second);

        if (PG.count(h) == 0) {
            ans = tree;
            cerr << "found the tree MEX" << endl;
            return true;
        }
        all[size].insert({h, tree});

        bool finish = true;
        rep(i, N) {
            ++iters[i];
            if (iters[i] == all[distr[i]].end()) {
                iters[i] = all[distr[i]].begin();
                continue;
            }
            finish = false;
            break;
        }
        if (finish) break;
    }
    return false;
}

bool backtrack(int i, int n, int s, int N) {
    distr[i] = n;
    s += n;
    if (s == N) {
        repx(j, i + 1, distr.size()) distr[j] = 0;
        if (visit_all_in_distr(N)) return true;
    } else {
        repx(k, 1, min(N - s + 1, n + 1)) {
            if (backtrack(i + 1, k, s, N)) return true;
        }
    }
    return false;
}

int build(Tree &T) {
    vector<int> R;
    for (Tree &child : T.children) {
        R.push_back(build(child));
    }
    int root = next_id--;
    for (int r : R) E.push_back({r, root});
    return root;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    G.resize(N);
    rep(j, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    P.resize(3 * N + 1);
    P[0] = 1;
    P[1] = chrono::steady_clock::now().time_since_epoch().count() % MOD;
    rep(i, 3 * N) P[i + 1] = (__int128)P[i] * P[1] % MOD;

    hashtree(0, 0);

    all.push_back({});
    all.push_back({{(P[1] + 2) % MOD, {2, {}}}});

    while (true) {
        int n = all.size();
        all.push_back({});
        distr.assign(n, 0);

        cerr << "finding trees of size " << n << endl;

        bool done = false;
        repx(k, 1, n) if (backtrack(0, k, 1, n)) {
            done = true;
            break;
        }

        if (done) break;
    }

    next_id = N;
    int root = build(ans);

    if (next_id < 0) {
        // G contains all possible subtrees
        E.clear();
        rep(u, N) for (int v : G[u]) if (u < v) E.push_back({u + 1, v + 1});
    } else {
        while (next_id > 0) {
            E.push_back({root, next_id});
            root = next_id;
            next_id -= 1;
        }
    }

    for (auto [u, v] : E) cout << u << " " << v << "\n";
}
