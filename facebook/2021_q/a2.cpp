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

const int INF = 1e8;

// from, to
int cost[26][26];

ll mincost(string& s, char into) {
    ll c = 0;
    for (char ch : s) {
        c += cost[ch - 'A'][into - 'A'];
    }
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    string s;
    string p;
    cin >> T;
    rep(t, T) {
        rep(i, 26) rep(j, 26) cost[i][j] = i == j ? 0 : INF;
        cin >> s;
        int K;
        cin >> K;
        rep(k, K) {
            cin >> p;
            cost[p[0] - 'A'][p[1] - 'A'] = 1;
        }
        rep(k, 26) rep(i, 26) rep(j, 26) cost[i][j] =
            min(cost[i][j], cost[i][k] + cost[k][j]);
        ll c = INT64_MAX;
        rep(i, 26) c = min(c, mincost(s, 'A' + i));
        cout << "Case #" << t + 1 << ": " << (c >= INF ? -1 : c) << "\n";
    }
}
