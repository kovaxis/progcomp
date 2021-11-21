#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int n;

int nodes[500001][4];

// node, parent
// min, max
pair<int, int> dp[500001][3];

pair<int, int> get_minmax(int i, int parent) {
    rep(j, nodes[i][3]) {
        if (nodes[i][j] == parent) {
            parent = j;
            break;
        }
    }
    auto& cache = dp[i][parent];
    if (cache.first != 0) return {cache.first - 1, cache.second - 1};
    cout << "finding minmax for node " << i << endl;
    int nmin = i;
    int nmax = i;
    rep(j, nodes[i][3]) {
        if (j == parent) continue;
        int child = nodes[i][j];
        cout << "checking childnode " << child << endl;
        auto mm = get_minmax(child, i);
        nmin = min(nmin, mm.first);
        nmax = max(nmax, mm.second);
    }
    cout << "minmax for node " << i << " is [" << nmin << ", " << nmax << "]"
         << endl;
    cache = {nmin + 1, nmax + 1};
    return {nmin, nmax};
}

bool can_be(int i, int parent) { auto }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    rep(i, n - 1) {
        int u, v;
        cin >> u >> v;
        u -= 1;
        v -= 1;
        nodes[u][nodes[u][3]++] = v;
        nodes[v][nodes[v][3]++] = u;
    }

    bool anyroot = false;
    rep(i, n) {
        int children = nodes[i][3];
        if (children >= 3) continue;
        pair<int, int> mm[2];
        rep(j, children) { mm[j] = get_minmax(nodes[i][j], i); }
        bool root = false;
        if (children < 2) {
            cout << "node " << i << " has single child [" << mm[0].first << ", "
                 << mm[0].second << "]\n";
            root = (mm[0].first - i) * (mm[0].second - i) > 0;
        } else {
            cout << "node " << i << " has double children [" << mm[0].first
                 << ", " << mm[0].second << "] [" << mm[1].first << ", "
                 << mm[1].second << "]\n";
            root = (mm[0].first - i) * (mm[0].second - i) > 0 &&
                   (mm[1].first - i) * (mm[1].second - i) > 0 &&
                   (mm[0].first - i) * (mm[1].first - i) < 0;
        }
        if (root) cout << i + 1 << " \n"[i == n - 1];
        anyroot |= root;
    }
    if (!anyroot) cout << "-1\n";
}
