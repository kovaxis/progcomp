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

int N;
// neighbor idx, 0 or 1
vector<pair<int, int>> adj[200001];
int parent[200001];

void find_parent(int i) {
    for (auto edge : adj[i]) {
        if (edge.first == parent[i]) continue;
        parent[edge.first] = i;
        find_parent(edge.first);
    }
}

// k:
// 0 => havent seen ones
// 1 => seen ones
// 2 => seen ones then zeros
ll dp[2][200001][2];

ll get_incdec(int i, int k, int is_dec) {
    if (k == 2) return 0;
    ll& cache = dp[isinc][i][k];
    if (cache != -1) return cache;
    ll reach = 1;
    for (auto edge : adj[i]) {
        if (edge.first == parent[i]) continue;
        int subk = k;
        if (edge.second != is_dec) {
            if (subk == 0) subk = 1;
        } else {
            if (subk == 1) subk = 2;
        }
        reach += get_incdec(edge.first, subk, is_dec);
    }
    /*cerr << "reaching node " << i + 1 << " reaches " << reach
         << " increasing paths (k=" << k << ")\n";*/
    cache = reach;
    return reach;
}

ll get_inc(int i, int k) { return get_incdec(i, k, false); }
ll get_dec(int i, int k) { return get_incdec(i, k, true); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    rep(i, N - 1) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u - 1].push_back({v - 1, c});
        adj[v - 1].push_back({u - 1, c});
    }
    find_parent(0);

    rep(i, N) rep(k, 2) {
        dp_inc[i][k] = -1;
        dp_dec[i][k] = -1;
    }
    ll pairs = 0;
    rep(i, N) {
        for (auto edge : adj[i]) {
            if (edge.first == parent[i]) continue;

            int incsubk = edge.second ? 1 : 0;
            int decsubk = edge.second ? 0 : 1;
            pairs += get_inc(edge.first, incsubk) *
                     (get_dec(i, decsubk) - get_dec(edge.first, decsubk));
            /*cerr << "pairs: nodes " << i + 1 << " -> " << edge.first + 1
                 << " are " << get_inc(edge.first, incsubk)
                 << " increasing paths and "
                 << (get_dec(i, decsubk) - get_dec(edge.first, decsubk))
                 << " decreasing paths\n";*/
        }
        pairs += get_dec(i, 0) - 1;
    }
    cout << pairs << '\n';
}
