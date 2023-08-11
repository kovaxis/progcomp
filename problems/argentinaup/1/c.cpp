#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (1) cerr

struct Edge {
    int u, v;
    int c;
    int j;
};

int N, M, cut_upto;
vector<vector<Edge>> G;
vector<int> seen;
vector<int> TS;
int TS_t;

bool dfs(int u) {
    if (seen[u] == 1) return true;
    if (seen[u] == -1) return false;
    seen[u] = 1;
    for (Edge e : G[u]) {
        if (e.c <= cut_upto) continue;
        if (dfs(e.v)) return true;
    }
    seen[u] = -1;
    return false;
}

bool has_cycle() {
    seen.assign(N, 0);
    rep(u, N) {
        if (dfs(u)) return true;
    }
    return false;
}

void toposort_dfs(int u) {
    if (seen[u]) return;
    seen[u] = true;
    for (Edge e : G[u]) {
        if (e.c <= cut_upto) continue;
        toposort_dfs(e.v);
    }
    TS[u] = TS_t++;
}

void toposort() {
    seen.assign(N, false);
    TS.assign(N, -1);
    TS_t = 0;
    rep(u, N) toposort_dfs(u);
}

int main() {
    cin >> N >> M;
    G.resize(N);
    rep(j, M) {
        int u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        G[u].push_back({u, v, c, j});
    }

    int l = 0, r = 1e9;
    while (l != r) {
        int m = (l + r) / 2;
        cut_upto = m;
        if (has_cycle()) l = m + 1;
        else r = m;
    }
    cut_upto = l;

    // toposort
    // biggest is the root, smallest is the leaf
    toposort();

    vector<int> ans;
    rep(u, N) for (Edge e : G[u]) {
        if (e.c > cut_upto) continue;
        // must go from big to small
        if (TS[e.u] < TS[e.v]) ans.push_back(e.j);
    }

    sort(ans.begin(), ans.end());

    cout << cut_upto << " " << ans.size() << endl;
    for (int j : ans) cout << j + 1 << " ";
    cout << endl;
}