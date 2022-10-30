#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (ll i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (ll i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

vector<int> p;

void solve(ll n) {
    if (n == 0) return;
    ll l = 0, r = sqrt(n) + 4;
    while (l != r) {
        ll m = (l + r) / 2;
        if (m * m < n - 1) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    ll k = l * l;
    ll s = k - (n - 1);
    ll large = n;
    repx(i, s, n) p[i] = --large;
    return solve(large);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        ll N;
        cin >> N;
        p.resize(N);
        solve(N);
        rep(i, N) cout << p[i] << " \n"[i == N - 1];
    }
}
