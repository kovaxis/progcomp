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

// [bricks][max_height]
long long combs[1024][1024];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    rep(h, 0, 2) {
        rep(b, 0, n + 1) { combs[b][h] = 0; }
    }
    rep(b, 0, 2) {
        rep(h, b, n + 1) { combs[b][h] = 1; }
    }
    rep(s_height, 2, n + 1) {
        rep(b_count, 2, n + 1) {
            combs[b_count][s_height] = combs[b_count][s_height - 1];
            if (b_count >= s_height) {
                combs[b_count][s_height] +=
                    combs[b_count - s_height][s_height - 1];
            }
        }
    }

    cout << (combs[n][n] - 1) << "\n";
}
