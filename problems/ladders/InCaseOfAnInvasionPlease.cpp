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

const ll INF = 1e18;

struct Flow {
    vector<vector<ll>> cap, flow;
    vector<ll> excess;
    vector<int> height;

    Flow() {}
    void resize(int N) { cap.assign(N, vector<ll>(N)); }

    // push as much excess flow as possible from u to v.
    void push(int u, int v) {
        ll f = min(excess[u], cap[u][v] - flow[u][v]);
        flow[u][v] += f;
        flow[v][u] -= f;
        excess[v] += f;
        excess[u] -= f;
    }

    // relabel the height of a vertex so that excess flow may be pushed.
    void relabel(int u) {
        int d = INT32_MAX;
        rep(v, cap.size()) if (cap[u][v] - flow[u][v] > 0) d =
            min(d, height[v]);
        if (d < INF) height[u] = d + 1;
    }

    // get the maximum flow on the network specified by `cap` with source `s`
    // and sink `t`.
    // node-to-node flows are output to the `flow` member.
    //
    // time: O(V^2 sqrt(E)) <= O(V^3)
    // memory: O(V^2)
    ll maxflow(int s, int t) {
        int N = cap.size(), M;
        flow.assign(N, vector<ll>(N));
        height.assign(N, 0), height[s] = N;
        excess.assign(N, 0), excess[s] = INF;
        rep(i, N) if (i != s) push(s, i);

        vector<int> q;
        while (true) {
            // find the highest vertices with excess
            q.clear(), M = 0;
            rep(i, N) {
                if (excess[i] <= 0 || i == s || i == t) continue;
                if (height[i] > M) q.clear(), M = height[i];
                if (height[i] >= M) q.push_back(i);
            }
            if (q.empty()) break;
            // process vertices
            for (int u : q) {
                bool relab = true;
                rep(v, N) {
                    if (excess[u] <= 0) break;
                    if (cap[u][v] - flow[u][v] > 0 && height[u] > height[v])
                        push(u, v), relab = false;
                }
                if (relab) {
                    relabel(u);
                    break;
                }
            }
        }

        ll f = 0;
        rep(i, N) f += flow[i][t];
        return f;
    }
};

int N, M, S;

vector<vector<pair<int, ll>>> G;
// heads[location]
vector<ll> people;
// total_people
ll total;
// (location, capacity)[shelter]
vector<pair<int, ll>> shelters;

// distance[shelter][location]
vector<vector<ll>> dists;

// bitmask(can reach shelter k)[location]
vector<int> reach;
Flow flow;

void dijkstra(vector<ll>& dists, int src) {
    dists.assign(G.size(), INF);
    dists[src] = 0;
    static set<pair<ll, int>> q;
    q.clear(), q.insert({0, src});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto edge : G[v]) {
            int to = edge.first;
            ll w = edge.second;
            if (dists[v] + w < dists[to]) {
                q.erase({dists[to], to});
                dists[to] = dists[v] + w;
                q.insert({dists[to], to});
            }
        }
    }
}

// check whether it's possible to evacuate everyone in the given time
bool feasible(ll time) {
    // for every location, calculate a bitmask of which shelters it can reach
    reach.assign(N, 0);
    rep(i, S) rep(j, N) reach[j] |= (dists[i][j] <= time) << i;

    // build a flow network with the following characteristics:
    int top = 1 << S;
    // 2^S + S + 2 nodes:
    //  - one source node for every bitmask
    //  - one sink node for every shelter
    //  - a supersource
    //  - a supersink
    flow.resize(top + S + 2);
    // for every bitmask, add an edge from the supersource, making each bitmask
    // a source. the source capacity of each bitmask is the amount of people
    // with the shelter reachability corresponding to the bitmask.
    rep(j, N) flow.cap[top + S][reach[j]] += people[j];
    // add an edge between every bitmask and the shelters it can reach
    rep(k, top) rep(i, S) if ((k >> i) & 1) flow.cap[k][top + i] = INF;
    // add edges between the shelters and the supersink, making each shelter a
    // sink. the sink capacity of each shelter is the capacity of the shelter.
    rep(i, S) flow.cap[top + i][top + S + 1] = shelters[i].second;

    // compute the maximum flow (amount of people that can move from the
    // locations to the shelters).
    ll f = flow.maxflow(top + S, top + S + 1);
    // if all people can flow to the shelters, this time is feasible.
    return f >= total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // read input
    cin >> N >> M >> S;
    people.resize(N);
    G.resize(N);
    shelters.resize(S);
    dists.resize(S);
    rep(j, N) cin >> people[j];
    rep(i, M) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u - 1].push_back({v - 1, w});
        G[v - 1].push_back({u - 1, w});
    }
    rep(i, S) {
        int s, c;
        cin >> s >> c;
        shelters[i] = {s - 1, c};
    }

    // count total people
    rep(j, N) total += people[j];

    // figure out distance from every shelter to every location
    rep(i, S) dijkstra(dists[i], shelters[i].first);

    // binary search in the answer (time)
    // min time: 0
    // max time: the maximum distance from some location to some shelter
    ll l = 0, r = 0;
    rep(i, S) rep(j, N) r = max(r, dists[i][j]);
    while (l != r) {
        ll m = l + (r - l) / 2;
        if (!feasible(m)) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    cout << l << "\n";
}
