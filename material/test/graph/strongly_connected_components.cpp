#include "../../graph/strongly_connected_components.cpp"
#include "gtest.h"

void dfs(vector<vector<int>> &G, vector<bool> &seen, int u) {
    if (seen[u]) return;
    seen[u] = true;
    for (int v : G[u]) dfs(G, seen, v);
}

vector<vector<bool>> can_reach(vector<vector<int>> &G) {
    int N = G.size();
    vector<vector<bool>> can(N, vector<bool>(N));
    rep(u, N) dfs(G, can[u], u);
    return can;
}

int main() {
    int N = 1000, M = 100000;
    vector<vector<int>> G = rand_graph_orient(N, M);
    vector<vector<bool>> can = can_reach(G);
    Scc scc = Scc(G);
    vector<vector<bool>> cancomp = can_reach(scc.G);
    auto show_info = [&]() {
        print_graph(G);
        cout << "toposort order:" << endl;
        rep(i, N) cout << "  node " << scc.order[i] + 1 << endl;
        cout << "components:" << endl;
        rep(i, N) cout << "  node " << i + 1 << " has component " << scc.comp[i] + 1 << endl;
        cout << "condensation ";
        print_graph(scc.G);
    };
    rep(u, N) {
        rep(v, N) {
            if (u == v) continue;
            if (scc.comp[u] == scc.comp[v]) {
                if (!(can[u][v] && can[v][u])) {
                    show_info();
                    cout << "nodes " << u + 1 << " & " << v + 1 << " have the same component, yet they can't reach each other" << endl;
                    throw "error";
                }
            }
            if (scc.comp[u] != scc.comp[v] && cancomp[scc.comp[u]][scc.comp[v]]) {
                if (!(can[u][v] && !can[v][u])) {
                    show_info();
                    cout << "nodes " << u + 1 << " & " << v + 1 << " have different components and u's component can reach v's, but u can't reach v or v can reach u" << endl;
                    throw "error";
                }
                assert(can[u][v] && !can[v][u]);
            }
        }
    }
    cout << "all ok" << endl;
}
