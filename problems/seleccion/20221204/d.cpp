#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, M;
vector<int> p, dp, cnt;
vector<vector<int>> G;

int getmaxpos(int u) {
    if (dp[u] != -1) return dp[u];
    int mp = p[u];
    for (int v : G[u]) {
        mp = min(mp, getmaxpos(v) - 1);
    }
    return dp[u] = mp;
}

void restrict_order() {
    dp.assign(N, -1);
    rep(i, N) getmaxpos(i);

    // cerr << "dp: ";
    // rep(i, N) cerr << dp[i] + 1 << " ";
    // cerr << endl;
}

// check if the given position array is feasible
bool feasible() {
    restrict_order();
    cnt.assign(N, 0);
    rep(i, N) {
        if (dp[i] < 0) return false;
        cnt[dp[i]] += 1;
    }

    int acc = 0;
    rep(i, N) {
        acc += cnt[i];
        if (acc > i + 1) return false;
    }

    return true;
}

// minimize position for `mini`
int solve(int mini) {
    int l = 0, r = N - 1;
    while (l < r) {
        int m = (l + r) / 2;
        int old = p[mini];
        p[mini] = m;
        bool feas = feasible();
        p[mini] = old;
        // cerr << "minimizing with p[" << mini + 1 << "] = " << m + 1 << ": " << feas << endl;
        if (feas) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    p.resize(N);
    G.resize(N);
    rep(i, N) cin >> p[i];
    rep(i, N) p[i] -= 1;
    rep(j, M) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        G[u].push_back(v);
    }

    rep(mini, N) {
        cout << solve(mini) + 1 << " \n"[mini == N - 1];
    }
}
