#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll INF = 1e18;

int N, M, K;
vector<vector<pair<int, ll>>> G;
vector<vector<ll>> D;

struct Node {
    int k, u;
    int dir, inc;

    bool operator<(const Node& r) const { return false; }
};

priority_queue<pair<ll, Node>> q;

void add(ll d, Node v) {
    D[v.k][v.u] = min(D[v.k][v.u], d);
    q.push({d, v});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;
    G.resize(N);
    rep(i, M) {
        ll u, v, w;
        cin >> u >> v >> w;
        G[u - 1].push_back({v - 1, w});
        G[v - 1].push_back({u - 1, w});
    }

    D.assign(K + 1, vector<ll>(N, INF));
    D[0][0] = 0;
    q.push({0, Node{0, 0, 0, 0}});
    while (!q.empty()) {
        ll d = q.top().first;
        Node v = q.top().second;
        q.pop();
        if (v.dir != 0) {
            Node nxt = {v.k, v.u + v.dir, v.dir, v.inc + 2};
            if (nxt.u >= 0 && nxt.u < N) {
                add(d + nxt.inc, nxt);
            }
        }
        if (d > D[v.k][v.u]) continue;
        for (auto edge : G[v.u]) {
            int to = edge.first;
            ll w = edge.second;
            add(d + w, Node{v.k, to, 0, 0});
        }
        if (v.k < K) {
            if (v.u + 1 < N) add(d + 1, Node{v.k + 1, v.u + 1, 1, 1});
            if (v.u - 1 >= 0) add(d + 1, Node{v.k + 1, v.u - 1, -1, 1});
        }
    }

    rep(i, N) {
        ll d = INF;
        rep(k, K + 1) d = min(d, D[k][i]);
        cout << d << " \n"[i == N - 1];
    }
}
