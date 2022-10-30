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
vector<vector<ll>> C;
vector<ll> rows;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    C.assign(N, vector<ll>(N));
    rep(i, N) rep(j, N) cin >> C[i][j];

    rows.assign(N, 0);
    rep(i, N) rep(j, N) rows[i] += C[i][j];

    sort(rows.begin(), rows.end());
    ll ans = 0;
    rep(i, N / 2) ans += rows[i + N / 2] - rows[i];
    cout << ans / 2 << endl;
}
