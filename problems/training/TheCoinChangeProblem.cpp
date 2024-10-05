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

int values[59];
long long ways_to_st[300][59];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> m >> n;
    rep(i, n) {
        int val;
        cin >> val;
        values[i] = val;
    }
    sort(&values[0], &values[n]);

    rep(i, n) { ways_to_st[0][i] = 1; }
    rep(i, 1, m + 1) {
        long long ways = 0;
        rep(j, n) {
            int val = values[j];
            if (i - val >= 0) {
                ways += ways_to_st[i - val][j];
            }
            ways_to_st[i][j] = ways;
        }
    }
    cout << ways_to_st[m][n - 1] << '\n';
}
