#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

const int INF = 1e9;

int N, M, K;
vector<int> C;
vector<vector<int>> G, D;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M >> K;
    C.resize(N);
    rep(i, N) cin >> C[i];

    G.resize(2 * N);
    rep(j, M) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int u1 = u, u2 = u + N;
        int v1 = v, v2 = v + N;
        if (C[u] != C[v]) swap(v1, v2);
        G[u1].push_back(v1);
        G[v1].push_back(u1);
        G[u2].push_back(v2);
        G[v2].push_back(u2);
    }

    {
        int n = 2 * N;
        D.assign(n, vector<int>(n, INF));
        rep(i, n) D[i][i] = 0;
        rep(i, n) for (int v : G[i]) D[i][v] = 1;
        rep(k, n) rep(u, n) rep(v, n) {
            D[u][v] = min(D[u][v], D[u][k] + D[k][v]);
        }
    }

    int diam = 0;
    rep(u, N) rep(v, N) {
        int d0 = D[u][v], d1 = D[u][v + N];
        int maxdist = 0;
        rep(k, K + 1) {
            // k = amount of ones in target bitstring
            int dist = min(d0 + k, d1 + (K - k));
            maxdist = max(maxdist, dist);
        }
        diam = max(diam, maxdist);
    }

    cout << diam << endl;
}
