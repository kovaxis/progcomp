#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const int N = 50001;
int M;
vector<vector<int>> G;
vector<vector<bool>> seen_cur, seen_prv, seen_nxt;
vector<queue<int>> Q1, Q2;
vector<vector<int>> ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> M;
    G.resize(N);
    rep(j, M) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    seen_cur.assign(N, vector<bool>(N, false));
    seen_prv.assign(N, vector<bool>(N, false));
    seen_nxt.assign(N, vector<bool>(N, false));
    Q1.assign(N, {});
    rep(u, N) Q1[u].push(u);
    rep(u, N) seen_prv[u][u] = true;

    while (true) {
        bool did_something = false;
        rep(i, N) {
            if (Q1[i].size()) did_something = true;
            while (Q1[i].size()) {
                int u = Q1[i].front();
                Q1[i].pop();

                for (int v : G[u])
                    if (seen_prv[i][v]) {
                        // back edge
                    } else if (seen_cur[i][v] || seen_nxt[i][v]) {
                        // loop

                    } else {
                        // new edge
                        Q2[i].push(v);
                        seen_nxt[i][v] = true;
                    }
            }
            swap(Q1[i], Q2[i]);
        }
        if (!did_something) break;
    }

    cout << ans.size() << "\n";
    for (auto &cyc : ans) {
        cout << cyc.size();
        for (int u : cyc) cout << " " << u;
        cout << "\n";
    }
}
