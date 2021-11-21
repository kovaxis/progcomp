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
    // and sink `t`. node-to-node flows are output to the `flow` global
    // variable.
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

int N;
Flow flow;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string tmps;
    cin >> N;
    flow.resize(N + 1);
    rep(u, N) {
        cin >> tmps;
        if (tmps == "*") {
            int v;
            cin >> v;
            v -= 1;
            flow.cap[u][v == 0 ? N : v] = INF;
        } else {
            int K = stoi(tmps);
            rep(j, K) {
                int v;
                cin >> v;
                v -= 1;
                flow.cap[u][v == 0 ? N : v] += 1;
            }
        }
    }
    ll out = flow.maxflow(0, N);
    if (out == INF)
        cout << "*\n";
    else
        cout << out + 1 << "\n";
}
