#include "../test.h"

vector<vector<int>> rand_graph_orient(int N, int M) {
    vector<vector<int>> G(N);
    if (N > 1) {
        rep(i, M) {
            int u = random_int(0, N);
            int v = random_int(0, N - 1);
            if (v >= u) v += 1;
            G[u].push_back(v);
        }
    }
    return G;
}

vector<vector<int>> rand_graph(int N, int M) {
    vector<vector<int>> G(N);
    if (N > 1) {
        rep(i, M) {
            int u = random_int(0, N);
            int v = random_int(0, N - 1);
            if (v >= u) v += 1;
            G[u].push_back(v);
            G[v].push_back(u);
        }
    }
    return G;
}

void print_graph(vector<vector<int>> &G) {
    cout << "graph:" << endl;
    rep(u, G.size()) {
        cout << "  node " << u + 1 << ":" << endl;
        for (int v : G[u]) {
            cout << "    to " << v + 1 << endl;
        }
    }
}