#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
ll B;
vector<ll> C, D;
vector<vector<int>> G;
vector<vector<ll>> freec;

void freec_dfs(int u) {
    freec[u].push_back(C[u]);
    for (int v : G[u]) {
        freec_dfs(v);
        freec[u].insert(freec[u].end(), freec[v].begin(), freec[v].end());
    }
    sort(freec[u].begin(), freec[u].end());
}

vector<ll> merge(vector<ll> &a, vector<ll> &b) {
    if (a.size() > b.size()) swap(a, b);
    vector<ll> out(b.size());
    rep(k, (int)b.size()) {
        out[k] = b[k];
        rep(j, min((int)a.size(), k + 1)) {
            out[k] = min(out[k], a[j] + b[k - j]);
        }
    }
    return out;
}

vector<ll> dfs(int u) {
    // do not paint u
    vector<ll> children;
    for (int v : G[u]) children.insert(children.end(), freec[v].begin(), freec[v].end());
    sort(children.begin(), children.end());
    vector<ll> nonpaint = {0};
    for (ll w : children) {
        nonpaint.push_back(nonpaint.back() + w);
    }

    // paint u
    vector<ll> paint = {0};
    for (int v : G[u]) {
        vector<ll> sub = dfs(v);
        paint = merge(paint, sub);
    }
    for (ll &w : paint) w += D[u];
    paint.insert(paint.begin(), 0);

    // get the minimum of both
    vector<ll> cost(max(nonpaint.size(), paint.size()));
    nonpaint.resize(cost.size(), 1e18);
    paint.resize(cost.size(), 1e18);
    rep(i, (int)cost.size()) cost[i] = min(nonpaint[i], paint[i]);

    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> B;
    C.resize(N);
    D.resize(N);
    G.resize(N);
    rep(u, N) {
        cin >> C[u] >> D[u];
        D[u] = C[u] - D[u];
        if (u > 0) {
            int p;
            cin >> p;
            G[p - 1].push_back(u);
        }
    }

    freec.resize(N);
    freec_dfs(0);

    vector<ll> cost = dfs(0);
    int mx = 0;
    rep(k, (int)cost.size()) {
        if (cost[k] <= B) mx = k;
    }

    cout << mx << endl;
}
