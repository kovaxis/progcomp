#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

const ll MOD = 100000000;

int n, m;
pair<int, int> acts[102];

// last_last_act, last_act
// ways
ll dp[102][102];

ll get_ways(int last_last, int last) {
    ll& out = dp[last_last][last];
    if (out != -1) return out;
    if (acts[last].second >= m) {
        out = 1;
        return out;
    }
    out = 0;
    rep(i, last + 1, n) {
        if (acts[i].first > acts[last].second) break;
        if (acts[i].first <= acts[last_last].second) continue;
        if (acts[i].second <= acts[last].second) continue;
        out = (out + get_ways(last, i)) % MOD;
    }
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (true) {
        cin >> m >> n;
        if (m == 0 || n == 0) break;
        rep(i, n) { cin >> acts[i].first >> acts[i].second; }
        acts[n++] = {-2, -1};
        acts[n++] = {-1, 0};
        sort(acts, acts + n);
        rep(i, n) rep(j, n) dp[i][j] = -1;

        cout << get_ways(0, 1) << '\n';
    }
}
