#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

template <class K, class V>
using umap = unordered_map<K, V>;

struct P {
    double x, y;
};

int N;
vector<vector<int>> G;
vector<vector<P>> a;
vector<vector<double>> dp;
umap<string, int> namemap;

double dist(P a, P b) {
    double x = a.x - b.x, y = a.y - b.y;
    return sqrt(x * x + y * y);
}

void dfs(int u, int p) {
    int k = a[u].size();
    for (int v : G[u])
        if (v != p) dfs(v, u);

    // cerr << "computing dp[" << u << "]" << endl;
    dp[u].resize(k);
    rep(j, k) {
        // minimum fiber to join all children with point u, j
        // cerr << "  computing dp[" << u << "][" << j << "]" << endl;
        double d = 0.;
        for (int v : G[u])
            if (v != p) {
                // minimum fiber to join point u, j with city v
                double subd = 1. / 0.;
                rep(vj, a[v].size()) subd =
                    min(subd, dist(a[u][j], a[v][vj]) + dp[v][vj]);
                d += subd;
            }
        dp[u][j] = d;
        // cerr << "  dp[" << u << "][" << j << "] = " << dp[u][j] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (true) {
        cin >> N;
        if (N == 0) break;
        a.resize(N), G.assign(N, vector<int>()), dp.resize(N);
        rep(i, N) {
            string s;
            int k;
            cin >> s >> k;
            namemap[s] = i;
            a[i].resize(k);
            rep(j, k) cin >> a[i][j].x >> a[i][j].y;
        }
        rep(i, N - 1) {
            string us, vs;
            cin >> us >> vs;
            int u = namemap[us], v = namemap[vs];
            G[u].push_back(v);
            G[v].push_back(u);
        }

        dfs(0, -1);
        double ans = 1. / 0.;
        for (double d : dp[0]) ans = min(ans, d);
        cout << fixed << setprecision(1) << setw(1) << ans << endl;
    }
}
