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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    vector<ll> wps;
    rep(t, T) {
        ll N, H;
        cin >> N >> H;
        wps.resize(N);
        rep(i, N) cin >> wps[i];
        sort(wps.begin(), wps.end());
        ll round = wps[N - 1] + wps[N - 2];
        int rounds = H / round;
        int rest;
        if (H % round <= 0)
            rest = 0;
        else if (H % round <= wps[N - 1])
            rest = 1;
        else
            rest = 2;
        cout << rounds * 2 + rest << "\n";
    }
}
