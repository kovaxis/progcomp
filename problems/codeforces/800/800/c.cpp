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

const ll INF = 1e18;

int N, M;
vector<vector<int>> G, Ginv;
vector<ll> D;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    G.resize(N), Ginv.resize(N);
    rep(i, M) {
        int u, v;
        cin >> u >> v;
        G[u - 1].push_back(v - 1);
        Ginv[v - 1].push_back(u - 1);
    }

    D.assign(N, INF);
    deque<int> q;
    D[N - 1] = 0;
    q.push_back(N - 1);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (int v : Ginv[u])
            if (D[v] == INF) D[v] = D[u] + 1, q.push_back(v);
    }

    map<int, int> active, nxt;
    active[0] = 0;
    int ans = -1;
    while (!active.empty()) {
                for (auto [u, d] : active) {
            cerr << "days to " << u + 1 << ": " << d << endl;
            if (u == N - 1) ans = d;
            for (int v : G[u])
                if (D[v] >= D[u]) d += 1;
            d += 1;
            for (int v : G[u])
                if (D[v] < D[u]) nxt[v] = max(nxt[v], d);
        }
        active.clear();
        swap(nxt, active);
    }

    cout << ans << endl;
}
