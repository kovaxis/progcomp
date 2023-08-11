// 5H

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)

#define cerr \
    if (0) cerr

vector<vector<int>> G;
vector<bool> seen;

bool dfs(int u) {
    if (seen[u]) return false;
    seen[u] = true;
    for (int v : G[u]) dfs(v);
    return true;
}

int main() {
    int N, M;
    cin >> N >> M;

    G.resize(2 * N - 2);
    rep(u, 2 * N - 2) {
        int v = (u + 2 * M - 2) % (2 * N - 2);
        if (v >= N) v = N - (v - N) - 2;
        G[u].push_back(v);
        G[v].push_back(u);
        cerr << u + 1 << " connects with " << v + 1 << endl;
        v = ((u - (2 * M - 2)) % (2 * N - 2) + 2 * N - 2) % (2 * N - 2);
        if (v >= N) v = N - (v - N) - 2;
        G[u].push_back(v);
        G[v].push_back(u);
        cerr << u + 1 << " connects with " << v + 1 << endl;
    }

    int ans = 0;
    seen.resize(2 * N - 2);
    rep(u, N) ans += dfs(u);
    cout << ans << endl;
}
