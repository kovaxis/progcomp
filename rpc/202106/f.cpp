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

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t, s, n;
    cin >> t >> s >> n;

    int upper = 0;
    int lastt = 0;
    rep(i, n) {
        int flipt;
        cin >> flipt;
        int fell = min(flipt - lastt, upper);
        upper -= fell;
        upper = s - upper;
        lastt = flipt;
    }
    int fell = min(t - lastt, upper);
    upper -= fell;
    cout << upper << endl;
}
