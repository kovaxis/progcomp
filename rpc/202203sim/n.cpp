#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, n) for (int i = 0; i < n; i++)

ll N;
vector<ll> a, b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    a.resize(N + 1);
    rep(i, N + 1) cin >> a[i];
    b.resize(N + 1);
    rep(i, N + 1) cin >> b[i];

    ll need = 0;
    ll cuts = 0;
    rep(ii, N + 1) {
        ll i = N - ii;
        ll needraw = b[i] - a[i];
        need += needraw;
        need = max(need, 0ll);
        ll needup = (need + 1) / 2;
        cuts += needup;
        need = needup;
    }
    if (need > 0) {
        cout << "-1\n";
    } else {
        cout << cuts << "\n";
    }
}