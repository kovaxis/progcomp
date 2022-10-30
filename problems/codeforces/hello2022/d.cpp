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
ll c[512][512];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        rep(x, 2 * N) rep(y, 2 * N) cin >> c[x][y];

        ll cost = 0;
        rep(x, N, 2 * N) rep(y, N, 2 * N) cost += c[x][y];
        vector<pair<int, int>> pos = {
            {0, N}, {0, 2 * N - 1}, {N - 1, N},     {N - 1, 2 * N - 1},
            {N, 0}, {N, N - 1},     {2 * N - 1, 0}, {2 * N - 1, N - 1}};
        ll extra = 1e10;
        for (auto p : pos) extra = min(extra, c[p.first][p.second]);
        cout << cost + extra << "\n";
    }
}
