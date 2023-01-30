#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N;
vector<vector<bool>> b;
vector<set<int>> ans;
vector<bool> seen;

void dp(int u) {
    if (seen[u]) return;
    seen[u] = true;
    ans[u].insert(u + 1);
    rep(p, N) if (b[p][u]) {
        dp(p);
        for (int x : ans[p]) ans[u].insert(x);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        b.assign(N, vector<bool>(N));
        rep(i, N) rep(j, N) {
            char c;
            cin >> c;
            b[i][j] = (c == '1');
        }

        seen.assign(N, false);
        ans.assign(N, {});
        rep(u, N) dp(u);

        rep(u, N) {
            cout << ans[u].size();
            for (int x : ans[u]) cout << " " << x;
            cout << "\n";
        }
    }
}
