#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

const ll INF = INT32_MAX;

int N;
ll K;
vector<vector<pair<int, ll>>> adj;

void dijkstra(const vector<vector<pair<int, ll>>>& adj, vector<ll>& dists,
              int src, ll placeholder_w) {
    auto cmp = [&dists](int a, int b) {
        if (dists[a] < dists[b])
            return true;
        else if (dists[a] > dists[b])
            return false;
        else
            return a < b;
    };

    for (auto& d : dists) d = INF;
    dists[src] = 0;
    static set<int, decltype(cmp)> q(cmp);
    q.clear();
    q.insert(src);
    while (!q.empty()) {
        int v = *q.begin();
        q.erase(q.begin());
        for (auto edge : adj[v]) {
            int to = edge.first;
            ll w = edge.second;
            if (w == -1) w = placeholder_w;
            if (dists[v] + w < dists[to]) {
                q.erase(to);
                dists[to] = dists[v] + w;
                q.insert(to);
            }
        }
    }
}

bool can_walk_with_c(ll C) {
    static vector<ll> dists;
    dists.resize(5 * N);
    dijkstra(adj, dists, 0, C);
    ll time = INT64_MAX;
    rep(c, 5) time = min(time, dists[c * N + N - 1]);
    return time <= K;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        int M;
        cin >> N >> M >> K;
        adj.clear();
        adj.resize(5 * N);
        rep(i, M) {
            int x, y, d;
            char color;
            cin >> x >> y >> d >> color;
            int c = color - 'a';
            adj[c * N + x - 1].push_back({c * N + y - 1, d});
            adj[c * N + y - 1].push_back({c * N + x - 1, d});
        }

        rep(i, N) rep(c1, 5) rep(c2, 5) {
            if (c1 == c2) continue;
            adj[c1 * N + i].push_back({c2 * N + i, -1});
        }

        ll l = 0, r = 1000000009;
        while (l != r) {
            int m = l + (r - l) / 2;
            if (can_walk_with_c(m)) {
                l = m + 1;
            } else {
                r = m;
            }
        }

        ll ans = l - 1;
        if (ans <= 0)
            cout << "impossible\n";
        else if (ans >= 1000000004)
            cout << "relaxing\n";
        else
            cout << ans << "\n";
    }
}
