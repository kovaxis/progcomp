#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int mod(int x, int m) {
    return (x % m + m) % m;
}

int N;
vector<int> a;
vector<pair<int, int>> ans;

int signof(int i) {
    return i % 2 ? -1 : 1;
}

pair<int, int> best(pair<int, int> a, pair<int, int> b, int sm) {
    if (a.first > -sm) return b;
    if (b.first > -sm) return a;
    if (a.first > b.first) return a;
    return b;
}

bool solve() {
    ans.clear();

    int sm = 0;
    rep(i, N) sm += a[i];

    if (sm > 0) {
        rep(i, N) a[i] *= -1;
        sm = -sm;
    }

    vector<pair<int, int>> dp[2];
    rep(k, 2) dp[k].resize(N + 1);

    dp[0][0] = {0, -1};    // dp[+][0] = 0
    dp[1][0] = {-1e9, -1}; // dp[-][0] = impossible

    a.push_back(0);
    repx(i, 1, N + 1) {
        // +
        dp[0][i] = best(dp[0][i - 1], dp[1][i - 1], sm);
        if (dp[0][i] == dp[0][i - 1]) dp[0][i].second = 0;
        else dp[0][i].second = 1;
        // -
        dp[1][i] = {dp[0][i - 1].first - 2 * a[i], 0};
    }

    int diff = dp[0][N].first;
    // cerr << "sm = " << sm << ", diff = " << diff << endl;
    if (diff != -sm) return false;

    int sign = dp[0][N].second;
    int prevsign = 0;
    invrep(i, N) {
        // cerr << "index " << i + 1 << " has sign " << sign << endl;
        if (!sign) ans.push_back({i, i + 1});
        if (prevsign) ans.back().second += 1;
        prevsign = sign;
        sign = dp[sign][i].second;
    }
    reverse(ans.begin(), ans.end());

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        a.resize(N);
        rep(i, N) cin >> a[i];

        if (solve()) {
            cout << ans.size() << "\n";
            for (auto [l, r] : ans) {
                cout << l + 1 << " " << r << "\n";
            }
        } else {
            cout << "-1\n";
        }
    }
}
