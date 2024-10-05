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

int n, m;
vector<int> cities[1001];

// city
// highest_bottleneck
int dp[1001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (true) {
        if (!(cin >> n)) break;
        cin >> m;
        rep(i, n) cities[i].clear();
        rep(i, m) {
            int u, v;
            cin >> u >> v;
            u -= 1;
            v -= 1;
            if (u == 0)
                dp[v] = -1;
            else
                cities[v].push_back(u);
        }
        dp[0] = -1;
        rep(i, n) {
            if (dp[i] == -1) {
                dp[i] = i;
                continue;
            }
            int bottleneck = dp[cities[i][0]];
            for (int parent : cities[i]) {
                if (bottleneck != dp[parent]) {
                    bottleneck = -1;
                    break;
                }
            }
            if (bottleneck == -1)
                dp[i] = i;
            else
                dp[i] = bottleneck;
        }
        ll disjoint = 0;
        rep(i, n) rep(j, i + 1, n) disjoint += (dp[i] != dp[j]);
        cout << disjoint << '\n';
    }
}
