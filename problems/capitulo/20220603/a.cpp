#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll INF = 1e18;

ll N, M, T;
vector<vector<pair<int, ll>>> G, invG;

vector<ll> dist, dist2;
vector<vector<int>> prv;
bool active = true;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> T;
    G.resize(N), invG.resize(N);
    rep(i, M) {
        ll u, v, t;
        cin >> u >> v >> t;
        G[u - 1].push_back({v - 1, t});
        invG[v - 1].push_back({u - 1, t});
    }

    prv.assign(N + 2, vector<int>(N, -1));
    dist.assign(N, INF);
    dist[0] = 0;
    int ans = 0;
    repx(t, 1, N + 1) {
        if (dist[N - 1] <= T) ans = max(ans, t);
        dist2.assign(N, INF);
        rep(u, N) {
            if (dist[u] > T) continue;
            // cerr << "reached " << u + 1 << " at time " << t << " with
            // distance "
            //     << dist[u] << endl;
            for (auto p : G[u]) {
                int v = p.first;
                ll d = dist[u] + p.second;
                if (d < dist2[v]) {
                    dist2[v] = d;
                    prv[t + 1][v] = u;
                }
            }
        }
        swap(dist, dist2);
    }

    vector<int> ansv;
    int u = N - 1;
    invrepx(t, 1, ans + 1) {
        ansv.push_back(u);
        u = prv[t][u];
    }
    cout << ansv.size() << '\n';
    invrep(i, ansv.size()) { cout << ansv[i] + 1 << " \n"[i == 0]; }
}
