#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

int n;
// from, to
// smoke, color
pair<int, int> dp[102][102];

pair<int, int> optimal_smoke(int from, int to) {
    if (dp[from][to].second != -1) {
        return dp[from][to];
    }
    pair<int, int> minimal = {-1, 0};
    rep(split, from + 1, to) {
        pair<int, int> l = optimal_smoke(from, split);
        pair<int, int> r = optimal_smoke(split, to);
        pair<int, int> x = {l.first + r.first + l.second * r.second,
                            (l.second + r.second) % 100};
        if (minimal.first == -1 || x.first < minimal.first) {
            minimal = x;
        }
    }
    dp[from][to] = minimal;
    return minimal;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (true) {
        if (!(cin >> n)) {
            break;
        }
        rep(i, n) {
            rep(j, n + 1) { dp[i][j].second = -1; }
            int col;
            cin >> col;
            dp[i][i + 1] = {0, col};
        }
        cout << optimal_smoke(0, n).first << '\n';
    }
}
