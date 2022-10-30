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
vector<vector<pair<int, int>>> G;
vector<int> ans;

bool solve() {
    rep(i, N) if (G[i].size() > 2) return false;
    int v, p = -1;
    rep(i, N) if (G[i].size() == 1) v = i;
    rep(i, N - 1) {
        for (auto c : G[v])
            if (c.first != p) {
                ans[c.second] = i % 2 ? 2 : 3;
                p = v, v = c.first;
                break;
            }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        G.assign(N, {});
        ans.resize(N - 1);
        rep(i, N - 1) {
            int u, v;
            cin >> u >> v;
            G[u - 1].push_back({v - 1, i});
            G[v - 1].push_back({u - 1, i});
        }

        if (solve()) {
            rep(i, N - 1) cout << ans[i] << " \n"[i == N - 2];
        } else {
            cout << "-1\n";
        }
    }
}
