#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll MOD = 1e9 + 7;

int N, M, K, X;
vector<vector<int>> G;

void root(int u) {
    for (int v : G[u]) {
        rep(i, G[v].size()) if (G[v][i] == u) {
            G[v].erase(G[v].begin() + i);
            break;
        }
        root(v);
    }
}

/*
u = subtree root node index
x = exact amount of nodes with color K in subtree
m =
    0: color[u] < K
    1: color[u] = K
    2: color[u] > K
dp[u][x][m] = amount of colorings satisfying the above restrictions

m -> m'
<    <=>
=    <
>    <>

m -> mul'
<    K - 1
=    1
>    M - K

n = amount of children of u
j = index of a child of u, in range [0, n)
c_j = node index of child j
x' = an int array of size n

dp[u][x][m] = mul' * sum(prod(dp[c_j][x'_j][m'] forall j) forall arrays x' such
that sum(x'_j forall j) = x - (m == '='))




dp[u][x][m] = dp2[n][x]

i = range of children being considered is [0, i). therefore i is in range [0, n]
x = exact amount of nodes with color K being multiplied
dp[i][x]

dp2[0][0] = 1
dp2[0][x] = 0
dp2[i][x] = sum(dp[c_{i-1}][x'][m'] * dp2[i-1][x - x'] forall x' in [0, x])
*/

ll dp(int u, int x, int m);

ll dp2mem[100009][11];
ll dp2(int u, int mb, int i, int x) {
    // cerr << "  consulting dp2[" << (i == 0 ? -1 : G[u][i - 1] + 1) << "][" <<
    // x
    //     << "] (u = " << u + 1 << ", mb = "
    //     << " <"[mb & 1] << " ="[(mb >> 1) & 1] << " >"[(mb >> 2) & 1] << ")"
    //     << endl;
    if (i == 0) return x == 0 ? 1 : 0;
    if (x < 0) return 0;
    ll& cache = dp2mem[G[u][i - 1]][x];
    if (cache != -1) {
        // cerr << "    cached value exists" << endl;
        return cache;
    }
    ll res = 0;
    rep(x2, x + 1) {
        ll dp1 = 0;
        rep(m, 3) {
            if (((mb >> m) & 1) == 0) continue;
            dp1 += dp(G[u][i - 1], x2, m);
            dp1 %= MOD;
        }
        res += dp1 * dp2(u, mb, i - 1, x - x2) % MOD;
        res %= MOD;
    }
    // cerr << "  dp2[" << G[u][i - 1] + 1 << "][" << x << "] (u = " << u + 1
    //     << ", mb = "
    //     << " <"[mb & 1] << " ="[(mb >> 1) & 1] << " >"[(mb >> 2) & 1]
    //     << ") = " << res << endl;
    return cache = res;
}

ll dpmem[100009][11][3];
ll dp(int u, int x, int m) {
    if (dpmem[u][x][m] != -1) return dpmem[u][x][m];
    const int mmap[3] = {7, 1, 5};
    int mb = mmap[m];

    for (int v : G[u]) rep(x2, x + 1) dp2mem[v][x2] = -1;
    ll res = dp2(u, mb, G[u].size(), x - (m == 1));

    ll mulmap[3] = {K - 1, 1, M - K};
    res = res * mulmap[m] % MOD;

    // cerr << "dp[" << u + 1 << "][" << x << "]["
    //     << "<=>"[m] << "] = " << res << endl;
    return dpmem[u][x][m] = res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    G.resize(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        G[u - 1].push_back(v - 1);
        G[v - 1].push_back(u - 1);
    }
    cin >> K >> X;

    root(0);

    rep(u, N) rep(x, X + 1) rep(m, 3) dpmem[u][x][m] = -1;
    ll ans = 0;
    rep(x, X + 1) rep(m, 3) ans = (ans + dp(0, x, m)) % MOD;
    cout << ans << endl;
}
