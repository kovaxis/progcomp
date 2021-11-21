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

const char patterns[6][4] = {
    "abc", "acb", "bac", "bca", "cab", "cba",
};
ll cost_to[6][200002];
string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, Q;
    cin >> n >> Q;
    cin >> s;
    rep(p, 6) rep(i, n) {
        char wanted = patterns[p][i % 3];
        cost_to[p][i + 1] = cost_to[p][i] + (wanted != s[i]);
    }
    rep(q, Q) {
        int l, r;
        cin >> l >> r;
        ll mincost = INT64_MAX;
        rep(p, 6) mincost = min(mincost, cost_to[p][r] - cost_to[p][l - 1]);
        cout << mincost << '\n';
    }
}
