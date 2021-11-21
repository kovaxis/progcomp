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

int N[2];
vector<set<int>> adj[2];

// longest paths down from every node
// longdn[graph][node] = {1st longest, 2nd longest}
vector<pair<int, int>> longdn[2];
// global longest path from each node
// longest[graph][node] = longest path to any node
vector<int> longest[2];

// ordered list of lengths of the second graph
vector<int> jlens;
// inverted accumulated sum of jlens:
// jsums[j] = sum(jlens[j:])
vector<ll> jsums;

// get the longest path down for each node (its depth)
// also compute the 2nd longest path down
int get_longdn(int l, int i) {
    int len[2] = {0, 0};
    for (int child : adj[l][i]) {
        int dn = get_longdn(l, child) + 1;
        if (dn > len[0])
            len[1] = len[0], len[0] = dn;
        else if (dn > len[1])
            len[1] = dn;
    }
    longdn[l][i] = {len[0], len[1]};
    return len[0];
}

// check the longest path up, and store the max of the longest path down and up
// in `longest[l][i]`. l = graph, i = node, superlen = length of the longest
// path up from `i`
void get_longup(int l, int i, int superlen) {
    auto& dn_full = longdn[l][i];
    longest[l][i] = max(dn_full.first, superlen);
    for (int child : adj[l][i]) {
        int dn = dn_full.first;
        if (dn == longdn[l][child].first + 1) dn = dn_full.second;
        get_longup(l, child, max(superlen + 1, dn + 1));
    }
}

// make sure each node is connected only to its children
void makeroot(int l, int i) {
    for (int child : adj[l][i]) {
        adj[l][child].erase(i);
        makeroot(l, child);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (true) {
        // read input
        if (!(cin >> N[0])) break;
        if (!(cin >> N[1])) break;
        rep(l, 2) {
            adj[l].clear();
            adj[l].resize(N[l]);
            longdn[l].resize(N[l]);
            longest[l].resize(N[l]);
        }
        jsums.clear();
        jsums.resize(N[1] + 1);
        rep(l, 2) rep(i, N[l] - 1) {
            int u, v;
            cin >> u >> v;
            adj[l][u - 1].insert(v - 1);
            adj[l][v - 1].insert(u - 1);
        }

        // traverse graphs
        rep(l, 2) makeroot(l, 0);
        rep(l, 2) get_longdn(l, 0);
        rep(l, 2) get_longup(l, 0, 0);

        // compute sum of tree size for all i, j pairs

        // precompute size floor (max of the sizes of each tree by itself)
        ll v = 0;
        rep(l, 2) for (int len : longest[l]) v = max(v, (ll)len);
        v -= 1;

        // prepare the lengths of the second tree
        jlens = longest[1];
        sort(jlens.begin(), jlens.end());
        invrep(j, N[1]) jsums[j] = jsums[j + 1] + jlens[j];

        // sum max(v, longest[0][i] + longest[0][j]) for every pair i, j
        ll gsum = 0;
        for (int ilen : longest[0]) {
            // equivalent to:
            // for(int jlen : longest[1]) gsum += max(v, ilen + jlen);
            ll idx = lower_bound(jlens.begin(), jlens.end(), v - ilen) -
                     jlens.begin();
            gsum += idx * v;
            gsum += ilen * (N[1] - idx) + jsums[idx];
        }

        double ans = (double)gsum / (double)((ll)N[0] * (ll)N[1]) + 1.;
        cout << fixed << setw(3) << setprecision(3) << ans << '\n';
    }
}
