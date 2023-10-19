#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

// gets the prime factorization of a number in O(sqrt(n))
vector<pair<ll, int>> factorize(ll x) {
    vector<pair<ll, int>> f;
    for (ll k = 2; x > 1; k++) {
        if (k * k > x) {
            f.push_back({x, 1});
            break;
        }
        int n = 0;
        while (x % k == 0) x /= k, n++;
        if (n > 0) f.push_back({k, n});
    }
    return f;
}

void solve() {

    ll P;
    cin >> P;
    vector<pair<ll, int>> f = factorize(P);

    ll s = 0;
    vector<ll> A;
    for (auto [x, n] : f) {
        rep(i, n) A.push_back(x), s += x;
    }

    if (s > 41) {
        cout << "-1\n";
        return;
    }

    while (s < 41) A.push_back(1), s += 1;

    cout << A.size();
    for (ll x : A) cout << " " << x;
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    rep(tc, TC) {
        cout << "Case #" << tc + 1 << ": ";
        solve();
    }
}
