#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, K;
vector<ll> a, ans;
ll x, y;

bool solve() {
    ans.clear();
    x = 0, y = 0;
    rep(i, N) x += a[i];
    rep(i, N) y += a[i] * a[i];

    ll r = y - x * x;
    if (r % 2 != 0) return false;
    r /= 2;

    if (x == 0) {
        if (K == 1 && r != 0) return false;
        if (r == 0)
            ans.push_back(0);
        else
            ans.push_back(1), ans.push_back(r);
        return true;
    }

    if (r % x == 0) {
        ans.push_back(r / x);
        return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        cout << "Case #" << tc + 1 << ":";

        cin >> N >> K;
        a.resize(N);
        rep(i, N) cin >> a[i];

        if (solve()) {
            for (ll n : ans) cout << " " << n;
            cout << "\n";
        } else {
            cout << " IMPOSSIBLE\n";
        }
    }
}
