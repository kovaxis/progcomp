#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

ll N, K, M;
vector<ll> a, b;

bool solve() {
    vector<pair<ll, ll>> have;
    rep(i, N) {
        ll x = a[i], cnt = 1;
        while (x % M == 0) x /= M, cnt *= M;
        if (!have.empty() && have.back().first == x)
            have.back().second += cnt;
        else
            have.push_back({x, cnt});
    }

    int q = 0;
    rep(j, K) {
        ll need = b[j], cnt = 1;
        while (need % M == 0) need /= M, cnt *= M;
        if (q >= have.size()) return false;
        if (have[q].first != need) return false;
        if (have[q].second < cnt) return false;
        have[q].second -= cnt;
        if (have[q].second == 0) q += 1;
    }

    if (q != have.size()) return false;

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N >> M;
        a.resize(N);
        rep(i, N) cin >> a[i];
        cin >> K;
        b.resize(K);
        rep(j, K) cin >> b[j];

        cout << (solve() ? "Yes" : "No") << "\n";
    }
}
