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

// hackproof unordered map hash
struct Hash {
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
using umap = unordered_map<T, U, Hash>;

// hackproof unordered_set
template <class T>
using uset = unordered_set<T, Hash>;

int N;
vector<vector<int>> G;
vector<int> isblack;

struct Cap {
    // has at least 1 black in the subtree.
    bool pull;
    // can always win as long as the chip is directly above the subtree.
    bool winalways;
    // can win as long as the chip is directly above the subtree, and the last
    // pull was not done with any black in the subtree.
    bool winsometimes;
};

vector<Cap> dpdown, dpup;

Cap dp(int u, int p) {
    Cap cap = {};
    int pullers = isblack[u], canwinsometimes = isblack[u];
    for (int c : G[u]) {
        if (c == p) continue;
        Cap sub = dfs(c, u);
        cap.pull |= sub.pull;
        cap.winalways |= sub.winalways;
        canwinsometimes |= sub.winsometimes;
        pullers += sub.pull;
    }
    cap.pull |= isblack[u];
    cap.winsometimes = isblack[u];
    if (canwinsometimes && pullers >= 2) cap.winalways |= true;
    cap.winsometimes |= cap.winalways;
    return dpdown[u] = cap;
}

// node, parent -> Cap
vector<umap<int, Cap>> dpmem;
Cap dp(int u, int p) {
    if (dpmem[u].count(p)) return dpmem[u][p];
    Cap cap = {};
    int pullers = isblack[u], canwinsometimes = isblack[u];
    for (int c : G[u]) {
        if (c == p) continue;
        Cap sub = dp(c, u);
        cap.pull |= sub.pull;
        cap.winalways |= sub.winalways;
        canwinsometimes |= sub.winsometimes;
        pullers += sub.pull;
    }
    cap.pull |= isblack[u];
    cap.winsometimes = isblack[u];
    if (canwinsometimes && pullers >= 2) cap.winalways |= true;
    cap.winsometimes |= cap.winalways;
    /*cerr << "node " << u + 1 << ", parent " << p + 1 << endl;
    cerr << "  pull: " << cap.pull << endl;
    cerr << "  winalways: " << cap.winalways << endl;
    cerr << "  winsometimes: " << cap.winsometimes << endl;*/
    return dpmem[u][p] = cap;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    G.assign(N, {});
    isblack.resize(N);
    rep(i, N) cin >> isblack[i];
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        G[u - 1].push_back(v - 1);
        G[v - 1].push_back(u - 1);
    }

    dpmem.assign(N, {});
    vector<int> ans(N, 0);
    rep(i, N) {
        for (int c : G[i])
            if (dp(c, i).winsometimes) ans[i] = 1;
        if (isblack[i]) ans[i] = 1;
    }

    rep(i, N) cout << ans[i] << " \n"[i == N - 1];
}
