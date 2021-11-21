#include "../common.h"

// calculates the lowest common ancestor for any two nodes in O(log N) time,
// with O(N log N) preprocessing
struct Lca {
    int L;
    vector<vector<int>> up;
    vector<pair<int, int>> time;

    Lca() {}
    void init(const vector<vector<int>>& G) {
        int N = G.size();
        L = N <= 1 ? 0 : 32 - __builtin_clz(N - 1);
        up.resize(L + 1);
        rep(l, L + 1) up[l].resize(N);
        time.resize(N);
        int t = 0;
        visit(G, 0, 0, t);
        rep(l, L) rep(i, N) up[l + 1][i] = up[l][up[l][i]];
    }

    void visit(const vector<vector<int>>& G, int i, int p, int& t) {
        up[0][i] = p;
        time[i].first = t++;
        for (int edge : G[i]) {
            if (edge == p) continue;
            visit(G, edge, i, t);
        }
        time[i].second = t++;
    }

    bool is_anc(int up, int dn) {
        return time[up].first <= time[dn].first &&
               time[dn].second <= time[up].second;
    }

    int get(int i, int j) {
        if (is_anc(i, j)) return i;
        if (is_anc(j, i)) return j;
        int l = L;
        while (l >= 0) {
            if (is_anc(up[l][i], j))
                l--;
            else
                i = up[l][i];
        }
        return up[0][i];
    }
};

#ifndef NOMAIN_LCA

Lca lca;

void que(int i, int j, int ex) {
    int out = lca.get(i - 1, j - 1);
    cerr << "lca of (" << i << ", " << j << ") = " << out + 1 << endl;
    assert(out == ex - 1);
}

int main() {
    vector<pair<int, int>> conns = {
        {1, 2},   {1, 3},   {1, 4},  {2, 12}, {12, 13}, {12, 14},
        {14, 15}, {3, 5},   {3, 6},  {6, 7},  {7, 8},   {8, 9},
        {8, 10},  {10, 11}, {8, 18}, {4, 16}, {4, 17}};
    vector<vector<int>> G(18);
    for (auto edge : conns) {
        G[edge.first - 1].push_back(edge.second - 1);
        G[edge.second - 1].push_back(edge.first - 1);
    }

    // lca
    //
    //      1
    //    / | \ 
    //   2  3   4
    //  /  / \  | \ 
    // 12  5  6 16 17
    // | \     \ 
    // 13 14    7
    //    |     |
    //    15    8
    //        / | \ 
    //       9 10  18
    //          |
    //         11
    lca.init(G);
    que(13, 14, 12);
    que(11, 14, 1);
    que(18, 5, 3);
    que(5, 18, 3);
    que(15, 12, 12);
    que(15, 14, 14);
    que(13, 17, 1);
    que(16, 17, 4);
    que(6, 6, 6);
}

#endif
