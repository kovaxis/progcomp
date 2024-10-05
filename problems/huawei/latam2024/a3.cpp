#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int N = 50001;
int M;
vector<vector<int>> G;
vector<int> P, D;
vector<bool> seen;
queue<int> Q;
vector<vector<int>> ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> M;
    G.resize(N);
    rep(j, M) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int n = 0;
    rep(u, N) if (G[u].size()) n += 1;

    int x = M - n + 1;
    cout << x << "\n";
    rep(y, x) {
        cout << 0;
        // for (int u : cyc) cout << " " << u;
        cout << "\n";
    }
}
