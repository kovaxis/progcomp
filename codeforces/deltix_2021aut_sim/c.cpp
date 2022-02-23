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

int N, E;
vector<int> a;

// {first idx such that sum >= 1, first idx such that sum >= 2}
vector<pair<int, int>> dp;

int fact(int x) {
    int y = 0, k = 2;
    while (x > 1) {
        if (k * k > x) return min(y + 1, 2);
        while (x % k == 0) x /= k, y++;
        k += 1;
        if (y >= 2) break;
    }
    return min(y, 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N >> E;
        a.resize(N);
        rep(i, N) cin >> a[i];

        rep(i, N) a[i] = fact(a[i]);
        // rep(i, N) cerr << a[i] << " \n"[i == N - 1];

        dp.resize(N);
        invrep(i, N) {
            auto sub = i + E < N ? dp[i + E] : pair<int, int>{0, 0};
            if (a[i] == 0) dp[i] = {sub.first + 1, sub.second + 1};
            if (a[i] == 1) dp[i] = {0, sub.first + 1};
            if (a[i] >= 2) dp[i] = {0, 0};
            // cerr << "dp[" << i + 1 << "] = " << dp[i].first << ", "
            //     << dp[i].second << endl;
        }

        ll ans = 0;
        rep(i, N) ans += max(0, dp[i].second - max(dp[i].first, 1));
        // cerr << "ans = " << ans << endl;
        cout << ans << "\n";
    }
}
