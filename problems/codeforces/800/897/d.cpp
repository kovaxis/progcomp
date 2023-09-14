#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, K;
vector<int> B;
bool ans;

vector<int> seenfrom, depth;

void dfs(int u, int s, int d) {
    if (seenfrom[u] != -1) {
        if (seenfrom[u] != s) {
            if (K == 1) ans = false;
            return;
        }
        int cycle = d - depth[u];
        if (K != cycle) ans = false;
        if (depth[u] != 0 && K == 1) ans = false;
        // cerr << "found cycle of length " << cycle << " from " << s << endl;
        return;
    }
    seenfrom[u] = s;
    depth[u] = d;
    return dfs(B[u], s, d + 1);
}

bool solve() {
    ans = true;
    seenfrom.assign(N, -1);
    depth.assign(N, -1);
    rep(u, N) dfs(u, u, 0);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> K;
        B.resize(N);
        rep(i, N) cin >> B[i];
        rep(i, N) B[i] -= 1;
        cout << (solve() ? "YES" : "NO") << "\n";
    }
}
