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

int N, M;
vector<vector<int>> G;

vector<int> stk;
vector<int> stkpos;
vector<bool> seen, incycle;
vector<int> cycle;

int dfs(int u) {
    if (seen[u]) {
        if (stkpos[u] != -1 && stkpos[u] < (int)stk.size() - 2) {
            // cycle between stkpos[u] and end of stack
            return stkpos[u];
        }
        return stk.size();
    }
    seen[u] = true;
    stkpos[u] = stk.size();
    stk.push_back(u);

    int cycle_up_to = stk.size();
    for (int v : G[u]) {
        cycle_up_to = min(cycle_up_to, dfs(v));
    }

    if (stkpos[u] >= cycle_up_to) incycle[u] = true;

    stk.pop_back();
    stkpos[u] = -1;
    return cycle_up_to;
}

bool dfs2(int u) {
    if (seen[u]) {
        if (stkpos[u] != -1 && stkpos[u] < (int)stk.size() - 2) {
            // cycle between stkpos[u] and end of stack
            repx(i, stkpos[u], (int)stk.size()) {
                cycle.push_back(stk[i]);
            }
            return true;
        }
        return false;
    }
    seen[u] = true;
    stkpos[u] = stk.size();
    stk.push_back(u);

    for (int v : G[u])
        if (dfs2(v)) return true;

    stk.pop_back();
    stkpos[u] = -1;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        G.assign(N, {});
        rep(j, M) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            cerr << "edge between " << u + 1 << " and " << v + 1 << endl;
            G[u].push_back(v);
            G[v].push_back(u);
        }

        stk.clear();
        stkpos.assign(N, -1);
        seen.assign(N, false);
        incycle.assign(N, false);
        rep(u, N) dfs(u);

        int U = -1;
        rep(u, N) if (incycle[u] && G[u].size() >= 4) {
            // fish node
            U = u;
            break;
        }

        if (U == -1) {
            cout << "NO\n";
            continue;
        }

        stk.clear();
        stkpos.assign(N, -1);
        seen.assign(N, false);
        cycle.clear();
        dfs2(U);
        assert(!cycle.empty());

        int n = cycle.size();
        rep(i, n) if (cycle[i] == U) {
            rotate(cycle.begin(), cycle.begin() + i, cycle.end());
        }
        map<int, int> cyc;
        rep(i, n) cyc[cycle[i]] = i;

        cerr << "cycle:";
        rep(i, n) cerr << " " << cycle[i] + 1;
        cerr << endl;

        map<int, int> conn;

        for (int v : G[U]) {
            if (cyc.count(v)) conn[cyc[v]] = v;
            else conn[-1 - v] = v;
        }

        cerr << "connected nodes:" << endl;
        for (auto [i, v] : conn) {
            cerr << "  " << i << ": " << v + 1 << endl;
        }

        // use the last two for the cycle, and the first two for fish
        assert(conn.size() >= 4);
        int c1i = (--conn.end())->first;
        int c0i = (--(--conn.end()))->first;
        int f0 = conn.begin()->second;
        int f1 = (++conn.begin())->second;

        vector<int> cycle2;
        cycle2.push_back(U);
        repx(i, c0i, c1i + 1) cycle2.push_back(cycle[i]);

        vector<pair<int, int>> E;
        rep(i, cycle2.size()) {
            int u = cycle2[i], v = cycle2[(i + 1) % cycle2.size()];
            E.push_back({u, v});
            cerr << "using cycle edge " << u + 1 << ", " << v + 1 << endl;
        }
        cerr << "using fish edge " << U + 1 << ", " << f0 + 1 << endl;
        E.push_back({U, f0});
        cerr << "using fish edge " << U + 1 << ", " << f1 + 1 << endl;
        E.push_back({U, f1});

        cout << "YES\n";
        cout << E.size() << "\n";
        for (auto [u, v] : E) {
            cout << u + 1 << " " << v + 1 << "\n";
        }
    }
}
