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

int N;
vector<set<int>> adj;

void makeroot(int i) {
    for (int child : adj[i]) {
        adj[child].erase(i);
        makeroot(child);
    }
}

// req_k, final_dist
pair<int, int> dfs(int i) {
    if (adj[i].size() == 0) return {0, 0};
    int req_k = 1, min_dist = INT32_MAX, max_dist = INT32_MIN;
    for (int child : adj[i]) {
        auto sub = dfs(child);
        req_k = max(req_k, sub.first);
        int dist = sub.second + 1;
        min_dist = min(min_dist, dist);
        max_dist = max(max_dist, dist);
    }
    if (adj.size() > 1) req_k = max(req_k, max_dist + 1);
    return {req_k, min_dist};
}

// req_k
int base_dfs(int i) {
    if (adj[i].size() == 0) return 0;
    int req_k = 1, max_dist[2] = {INT32_MIN, INT32_MIN};
    for (int child : adj[i]) {
        auto sub = dfs(child);
        req_k = max(req_k, sub.first);
        int dist = sub.second + 1;
        if (dist > max_dist[0])
            max_dist[1] = max_dist[0], max_dist[0] = dist;
        else if (dist > max_dist[1])
            max_dist[1] = dist;
    }
    req_k = max(req_k, max_dist[1] + 1);
    req_k = max(req_k, max_dist[0]);
    return req_k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        adj.clear();
        adj.resize(N);
        rep(i, N - 1) {
            int u, v;
            cin >> u >> v;
            adj[u - 1].insert(v - 1);
            adj[v - 1].insert(u - 1);
        }

        makeroot(0);
        cout << base_dfs(0) << '\n';
    }
}
