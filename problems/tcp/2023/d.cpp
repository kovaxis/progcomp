#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

struct Dists {
    int D[300][300];
};

const int INF = 1e9 + 1;

int N;
Dists cost;
Dists miss[300];

void half(int l, int r, const Dists &up) {
    if (r - l == 1) {
        miss[l] = up;
        return;
    }
    int m = (l + r) / 2;
    Dists D = up;
    repx(i, m, r) rep(u, N) rep(v, N) D.D[u][v] = min(D.D[u][v], D.D[u][i] + D.D[i][v]);
    half(l, m, D);
    D = up;
    repx(i, l, m) rep(u, N) rep(v, N) D.D[u][v] = min(D.D[u][v], D.D[u][i] + D.D[i][v]);
    half(m, r, D);
}

int main() {
    int M;
    cin >> N >> M;
    rep(u, N) rep(v, N) cost.D[u][v] = INF;
    rep(u, N) cost.D[u][u] = 0;
    vector<pair<int, int>> E(M);
    rep(j, M) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        cost.D[u][v] = w;
        cost.D[v][u] = w;
        E[j] = {u, v};
    }

    half(0, N, cost);

    rep(j, M) {
        auto [u, v] = E[j];
        int ans = INF;
        rep(k, N) if (k != u && k != v) {
            ans = min(ans, cost.D[u][k] + miss[u].D[k][v]);
        }
        if (ans == INF) ans = -1;
        cout << ans << "\n";
    }
}
