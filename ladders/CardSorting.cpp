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

int C, N;
int cards[1000];

int dp[1000];

pair<int, int> cards_raw[1000];
int permutation[8];
bool used[8];

int lis() {
    cards[C * N] = INT32_MAX;
    rep(i, C * N + 1) {
        dp[i] = 1;
        rep(j, i) if (cards[i] >= cards[j]) dp[i] = max(dp[i], dp[j] + 1);
    }
    return dp[C * N] - 1;
}

int permute(int i) {
    if (i >= C) {
        rep(j, C * N) cards[j] =
            permutation[cards_raw[j].first] * N + cards_raw[j].second;
        return C * N - lis();
    }

    int mincost = INT32_MAX;
    rep(j, C) {
        if (used[j]) continue;
        permutation[i] = j;
        used[j] = true;
        mincost = min(mincost, permute(i + 1));
        used[j] = false;
    }
    return mincost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> C >> N;
    rep(i, C * N) {
        int c, n;
        cin >> c >> n;
        cards_raw[i].first = c - 1;
        cards_raw[i].second = n - 1;
    }
    cout << permute(0) << '\n';
}
