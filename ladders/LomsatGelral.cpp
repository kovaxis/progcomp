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

struct Node {
    map<int, int> cols;
    int mcount;
    ll csum;

    Node(int col) : mcount(1), csum(col) { cols.insert({col, 1}); }

    void merge(Node& rhs) {
        if (rhs.cols.size() > cols.size()) swap(*this, rhs);
        for (auto c : rhs.cols) {
            int x = (cols[c.first] += c.second);
            if (x > mcount) mcount = x, csum = 0;
            if (x >= mcount) csum += c.first;
        }
    }
};

int N;
vector<vector<int>> G;
vector<int> color;
vector<ll> sums;

void dfs(int i, int p, Node* out) {
    Node node(color[i]);
    for (int c : G[i])
        if (c != p) dfs(c, i, &node);
    sums[i] = node.csum;
    if (out) out->merge(node);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    G.resize(N), color.resize(N), sums.resize(N);
    rep(i, N) cin >> color[i];
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        G[u - 1].push_back(v - 1);
        G[v - 1].push_back(u - 1);
    }

    dfs(0, 0, 0);
    rep(i, N) cout << sums[i] << " \n"[i == N - 1];
}
