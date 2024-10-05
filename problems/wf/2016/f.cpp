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

int N, K;
vector<string> names;
vector<int> P;
vector<ll> W;
vector<vector<int>> G;

vector<ll> D, min_d_to_leaf;

vector<int> C;
int pts;
priority_queue<pair<ll, int>> que;
vector<int> ans;

void d_dfs(int u) {
    if (P[u] != -1) D[u] += D[P[u]];
    D[u] += W[u];
    for (int v : G[u]) d_dfs(v);
}

void d_to_leaf_dfs(int u) {
    min_d_to_leaf[u] = W[u];
    if (G[u].size() == 0) return;
    ll d = 1e18;
    for (int v : G[u]) {
        d_to_leaf_dfs(v);
        d = min(d, min_d_to_leaf[v]);
    }
    min_d_to_leaf[u] += d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> K >> N;
    N += 1 + K;
    P.resize(N);
    names.resize(K);
    W.resize(N);
    rep(i, K) {
        cin >> names[i];
        cin >> P[i];
        if (P[i] == 0) P[i] = N - 1;
        else P[i] = K + P[i] - 1;
        cin >> W[i];
    }
    P[N - 1] = -1;
    rep(j, N - K - 1) {
        cin >> P[K + j];
        if (P[K + j] == 0) P[K + j] = N - 1;
        else P[K + j] = K + P[K + j] - 1;
        cin >> W[K + j];
    }

    G.resize(N);
    rep(i, N) {
        if (P[i] != -1) G[P[i]].push_back(i);
    }

    D.resize(N);
    min_d_to_leaf.resize(N);
    d_dfs(N - 1);
    d_to_leaf_dfs(N - 1);

    C.resize(N);
    rep(u, N) C[u] = G[u].size();
    pts += K;
    rep(u, K) que.push({-min_d_to_leaf[u], u});

    vector<int> order(K);
    rep(u, K) order[u] = u;
    sort(order.begin(), order.end(), [](int u, int v) {
        return D[u] < D[v];
    });
    ans.resize(K);
    for (int u : order) {
        while (que.size() && -que.top().first <= D[u]) {
            // move point up
            int v = que.top().second;
            que.pop();

            if (P[v] == -1) {
                // just die
                pts -= 1;
                continue;
            }

            C[P[v]] -= 1;
            if (C[P[v]] != 0) {
                // this point gets hidden
                pts -= 1;
            } else {
                // the head has moved up
                que.push({-min_d_to_leaf[P[v]], P[v]});
            }
        }

        ans[u] = pts + 1;
    }

    rep(i, K) {
        cout << names[i] << " " << ans[i] << "\n";
    }
}
