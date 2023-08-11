#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

const ll INF = 1e18;

struct Edge {
    int u, v;
    ll c, w, f = 0;
};

// find the minimum-cost flow among all maximum-flow flows.
//
// time: O(F V E)            F is the maximum flow
//       O(V E + F E log V)  if bellman-ford is replaced by johnson
struct Flow {
    int N, s, t;
    vector<vector<int>> G;
    vector<Edge> E;
    vector<ll> d, b;
    vector<int> p;

    Flow() {}
    Flow(int N, int s, int t) : N(N), s(s), t(t), G(N) {}

    void add_edge(int u, int v, ll c, ll w) {
        G[u].push_back(E.size());
        E.push_back({u, v, c, w});
        G[v].push_back(E.size());
        E.push_back({v, u, 0, -w});
    }

    // johnsons potentials: O(E log V)
    void calcdists() {
        if (b.empty()) {
            b.assign(N, 0);
            // code below only necessary if there are negative costs
            rep(i, N - 1) rep(ei, E.size()) {
                Edge &e = E[ei];
                if (e.f < e.c) b[e.v] = min(b[e.v], b[e.u] + e.w);
            }
        }
        p.assign(N, -1), d.assign(N, INF), d[s] = 0;
        priority_queue<pair<ll, int>> q;
        q.push({0, s});
        while (!q.empty()) {
            auto [w, u] = q.top();
            q.pop();
            if (d[u] < -w + b[u]) continue;
            for (int ei : G[u]) {
                auto e = E[ei];
                ll n = d[u] + e.w;
                if (e.f < e.c && n < d[e.v]) {
                    d[e.v] = n, p[e.v] = ei;
                    q.push({b[e.v] - n, e.v});
                }
            }
        }
        b = d;
    }

    ll solve() {
        b.clear();
        ll ff = 0;
        while (true) {
            calcdists();
            if (p[t] == -1) break;
            if (d[t] >= 0) break;

            ll f = INF;
            int cur = t;
            for (int cur = t; p[cur] != -1; cur = E[p[cur]].u)
                f = min(f, E[p[cur]].c - E[p[cur]].f);
            for (int cur = t; p[cur] != -1; cur = E[p[cur]].u)
                E[p[cur]].f += f, E[p[cur] ^ 1].f -= f;
            ff += f;
        }
        return ff;
    }
};

int N;
stringstream out;
vector<vector<int>> G;
vector<int> D, P;

void solve() {
    cerr << "building flow network" << endl;
    Flow mcmf(N + 2, N, N + 1);
    rep(u, N) {
        mcmf.add_edge(N, u, INF, 0);
        mcmf.add_edge(u, N + 1, INF, 0);
    }
    rep(u, N) for (int v : G[u]) {
        mcmf.add_edge(u, v, 1, -1);
        mcmf.add_edge(u, v, INF, 0);
    }

    cerr << "solving flow" << endl;
    mcmf.solve();

    cerr << "retrieving paths" << endl;
    vector<vector<int>> ans;
    while (true) {
        vector<int> path;
        int u = N;
        while (true) {
            bool found = false;
            for (int eid : mcmf.G[u]) {
                Edge &e = mcmf.E[eid];
                if (e.f > 0) {
                    e.f -= 1;
                    u = e.v;
                    found = true;
                    break;
                }
            }
            if (!found) break;
            path.push_back(u);
        }
        if (path.empty()) break;
        path.pop_back();
        ans.push_back(path);
    }

    cerr << "printing answers" << endl;

    // print ans
    out << ans.size() << "\n";
    for (auto &path : ans) {
        rep(i, (int)path.size()) {
            out << path[i] + 1;
            if (i < (int)path.size() - 1) out << " ";
        }
        out << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ifstream infile("inspection.in");
    stringstream input;
    input << infile.rdbuf();
    infile.close();

    input >> N;
    G.assign(N, {});
    rep(u, N) {
        int n;
        input >> n;
        rep(i, n) {
            int v;
            input >> v;
            v--;
            G[u].push_back(v);
        }
    }

    cerr << "read " << N << " nodes of input" << endl;

    solve();

    cerr << "writing output file" << endl;
    ofstream outfile("inspection.out");
    outfile << out.str();
    outfile.close();
}