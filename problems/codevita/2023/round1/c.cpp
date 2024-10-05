#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, M, ix, jx, H;
vector<vector<int>> lvl;
vector<vector<bool>> flood, seen;
int ans;

void dfs(int i, int j) {
    if (i < 0 || i >= N || j < 0 || j >= M) return;
    if (lvl[i][j] > H) return;
    if (flood[i][j]) return;
    flood[i][j] = true;
    dfs(i - 1, j);
    dfs(i + 1, j);
    dfs(i, j - 1);
    dfs(i, j + 1);
}

int dfs2(int i, int j, int l) {
    if (i < 0 || i >= N || j < 0 || j >= M) return 0;
    if (lvl[i][j] != l) return 0;
    if (!flood[i][j]) return 0;
    if (seen[i][j]) return 0;
    seen[i][j] = true;
    dfs2(i - 1, j, l);
    dfs2(i + 1, j, l);
    dfs2(i, j - 1, l);
    dfs2(i, j + 1, l);
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    lvl.assign(N, vector<int>(M));
    string s;
    getline(cin, s);
    rep(i, N) {
        getline(cin, s);
        stringstream ss(s);
        rep(j, M) {
            bool ok = (ss >> lvl[i][j] ? 1 : 0);
            if (!ok) {
                throw "error";
            }
        }
    }
    cin >> ix >> jx;
    cin >> H;

    flood.assign(N, vector<bool>(M));
    if (lvl[ix][jx] == 0) {
        dfs(ix, jx);
    }

    seen.assign(N, vector<bool>(M));
    rep(i, N) rep(j, M) if (lvl[i][j] > 0) {
        ans += dfs2(i, j, lvl[i][j]);
    }

    if (ans == 0) cout << "NONE" << endl;
    else cout << ans << endl;
}
