#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

struct Edge {
    int t, u, v;

    bool operator<(Edge r) const {
        return t < r.t;
    }
};

int N, T, K;
vector<vector<Edge>> G, E;
vector<int> A, newseen;
vector<bool> seen;
int ans;

void activate(int u) {
    if (seen[u]) return;
    seen[u] = true;
    for (Edge e : G[u]) {
        E[e.t].push_back(e);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> T;
    G.resize(N);
    rep(t, T) {
        int M;
        cin >> M;
        rep(j, M) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            G[u].push_back({t, u, v});
            G[v].push_back({t, v, u});
        }
    }
    cin >> K;
    A.resize(K);
    rep(i, K) cin >> A[i];
    rep(i, K) A[i] -= 1;

    // rep(u, N) sort(G[u].begin(), G[u].end());
    E.resize(T);

    seen.assign(N, false);
    activate(0);
    rep(ii, K) {
        ans += 1;
        int t = A[ii];

        newseen.clear();
        for (Edge e : E[t]) {
            newseen.push_back(e.u);
            newseen.push_back(e.v);
        }
        E[t].clear();
        for (int u : newseen) activate(u);

        if (seen[N - 1]) break;
        if (ii == K - 1) ans = -1;
    }

    cout << ans << endl;
}
