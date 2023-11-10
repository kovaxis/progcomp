#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

vector<ll> get_s(vector<vector<pair<ll, int>>> G, ll k) {
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<vector<pair<ll, int>>> G;
    int n, m;
    ll k;
    cin >> n >> m >> k;
    G.resize(n);
    for (int j = 0; j < m; j++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        u--, v--;
        G[u].push_back({w, v});
    }

    power(G, k);
}
