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

vector<bool> seen;
vector<int> cycle;

bool dfs(int u, int root) {
    if (seen[u]) {
        return u == root && cycle.size() >= 3;
    }
    seen[u] = true;
    cycle.push_back(u);

    for (int v : G[u])
        if (dfs(v, root)) return true;

    cycle.pop_back();
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
            G[u].push_back(v);
            G[v].push_back(u);
        }

        int U = -1;
        rep(u, N) {
            if (G[u].size() < 4) continue;
            // search for a cycle
            seen.assign(N, false);
            cycle.clear();
            dfs(u, u);
            if (cycle.empty()) continue;

            // use u as fish
            U = u;
            break;
        }

        if (U == -1) {
            cout << "NO\n";
            continue;
        }

        map<int, int> cyc;
        rep(i, cycle.size()) cyc[cycle[i]] = i;

        map<int, int> conn;
        for (int v : G[U]) {
            if (cyc.count(v)) {
                conn[cyc[v]] = v;
            } else {
                conn[-1 - v] = v;
            }
        }

        // use the last two for the cycle, and the first two for fish
        assert(conn.size() >= 4);
        int c1i = (--conn.end())->first;
        int c0i = (--(--conn.end()))->first;
        int f0 = conn.begin()->second;
        int f1 = (++conn.begin())->second;
        assert(c0i >= 0);
        assert(c1i >= 0);

        vector<int> cycle2;
        cycle2.push_back(U);
        repx(i, c0i, c1i + 1) cycle2.push_back(cycle[i]);

        vector<pair<int, int>> E;
        rep(i, cycle2.size()) E.push_back({cycle2[i], cycle2[(i + 1) % cycle2.size()]});
        E.push_back({U, f0});
        E.push_back({U, f1});

        cout << "YES\n";
        cout << E.size() << "\n";
        for (auto [u, v] : E) {
            cout << u + 1 << " " << v + 1 << "\n";
        }
    }
}
