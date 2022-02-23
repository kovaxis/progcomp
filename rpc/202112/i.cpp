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
vector<ll> T;
vector<pair<ll, int>> P;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    T.resize(N), P.resize(N);
    rep(i, N) cin >> T[i];
    rep(i, N) {
        cin >> P[i].first;
        P[i].second = i;
    }

    sort(P.begin(), P.end());
    ll total = 0, ans = 0;
    rep(j, N) {
        int t = P[j].first;
        if (t == -1) continue;
        int i = P[j].second;

        total += T[i];
        // solve p problems in t time
        // `total` computational time in `t` actual time
        ans = max(ans, (total + t - 1) / t);
    }

    cout << ans << endl;
}
