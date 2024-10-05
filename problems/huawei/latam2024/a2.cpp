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
vector<int> P, D;
vector<bool> seen;
queue<int> Q;
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

    P.resize(N), D.resize(N), seen.assign(N, false);
    rep(root, N) {
        if (seen[root]) continue;
        Q.push(root);
        seen[root] = true;
        P[root] = root;

        while (Q.size()) {
            int u = Q.front();
            Q.pop();
            for (int v : G[u]) {
                if (seen[v]) {
                    // loop
                    if (D[v] > D[u] || (D[u] == D[v] && u < v)) {
                        // cerr << "edge from " << u << " to " << v << " is a loop" << endl;
                        vector<int> from_u;
                        int uu = u;
                        while (uu != root) {
                            from_u.push_back(uu);
                            uu = P[uu];
                        }
                        vector<int> from_v;
                        int vv = v;
                        while (vv != root) {
                            from_v.push_back(vv);
                            vv = P[vv];
                        }
                        int last = root;
                        while (from_u.size() && from_v.size() && from_u.back() == from_v.back()) last = from_u.back(), from_u.pop_back(), from_v.pop_back();
                        from_u.push_back(last);
                        from_v.push_back(last);
                        reverse(from_u.begin(), from_u.end());
                        from_u.insert(from_u.end(), from_v.begin(), from_v.end());
                        ans.push_back(from_u);
                    }
                } else {
                    // cerr << "edge from " << u << " to " << v << " is new" << endl;
                    Q.push(v);
                    P[v] = u;
                    D[v] = D[u] + 1;
                    seen[v] = true;
                }
            }
        }
    }

    cout << ans.size() << "\n";
    for (auto &cyc : ans) {
        cout << cyc.size();
        for (int u : cyc) cout << " " << u;
        cout << "\n";
    }
}
