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

struct Num {
    ll x, p;
} nums[2];

int solve() {
    rep(i, 2) cin >> nums[i].x >> nums[i].p;
    ll dp = nums[1].p - nums[0].p;
    if (dp >= 7) return 1;
    if (dp <= -7) return -1;
    if (dp > 0) rep(j, dp) nums[1].x *= 10;
    if (dp < 0) rep(j, -dp) nums[0].x *= 10;
    if (nums[1].x > nums[0].x) return 1;
    if (nums[1].x < nums[0].x) return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        int ans = solve();
        if (ans == 1)
            cout << "<\n";
        else if (ans == -1)
            cout << ">\n";
        else
            cout << "=\n";
    }
}
