#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> ii;
vector<vector<ii>> edges;

void dfs(int v, int p, vector<ll> &d) {
    for (auto u : edges[v]) {
        if (u.first != p) {
            d[u.first] = d[v] + u.second;
            dfs(u.first, v, d);
        }
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    ll sum = 0;
    edges.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        ll w;
        cin >> a >> b >> w;
        a--;
        b--;
        edges[a].push_back(ii(b, w));
        edges[b].push_back(ii(a, w));
        sum = sum + 2LL * w;
    }

    vector<vector<ll>> dis(n, vector<ll>(n, 1e18));
    for (int i = 0; i < n; i++) {
        dis[i][i] = 0;
        dfs(i, -1, dis[i]);
    }

    while (q--) {
        int s, k, t;
        cin >> s >> k >> t;
        s--;
        k--;
        t--;

        if (dis[s][t] + dis[t][k] == dis[s][k]) {
            cout << "impossible\n";
            continue;
        }

        int lca = -1;
        for (int i = 0; i < n; i++) {
            if (dis[s][k] + dis[s][t] == 2LL * dis[s][i] + dis[k][t]) {
                lca = i;
                break;
            }
        }

        ll mini = sum;
        for (int i = 0; i < n; i++) {
            if (dis[s][k] + dis[k][i] == dis[s][i]) {
                mini = min(mini, sum - dis[s][i] + 2LL * dis[lca][k]);
            } else {
                mini = min(mini, sum - dis[s][i]);
            }
        }

        cout << mini << "\n";
    }

    return 0;
}
