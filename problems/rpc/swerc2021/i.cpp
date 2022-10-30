#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= 0; i--)
#define invrep(i, n) invrepx(i, 0, n)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m, ans = 0;
    ll x;
    cin >> n >> m;
    vector<ll> mini(n, n * 100), maxi(n, 0), ban(n, 0), L(n, -1), R(n, -1);
    vector<ll> pop;
    for (int i = 0; i < n; i++) {
        cin >> x;
        pop.push_back(x);
    }
    vector<ll> c;
    for (int i = 0; i < m; i++) {
        cin >> x;
        c.push_back(x);
        if (x / 100 < n && x % 100 == 0) ban[x / 100] = 1;
    }
    sort(c.begin(), c.end());
    ll in = 0;
    for (int i = 0; i < n; i++) {
        x = i * 100;
        while (in < c.size() - 1 && c[in + 1] <= x) in++;
        if (c[in] > x)
            L[i] = -1e15;
        else
            L[i] = c[in];
    }
    in = c.size() - 1;
    for (int i = n - 1; i >= 0; i--) {
        x = i * 100;
        while (in > 0 && c[in - 1] >= x) in--;
        if (c[in] < x) {
            R[i] = 1e15;
        }

        else
            R[i] = c[in];
    }
    vector<tuple<double, ll, ll> > sweep;
    for (int i = 0; i < n; i++) {
        if (ban[i]) continue;
        double dis = min(R[i] - i * 100, i * 100 - L[i]);
        // cout << dis << " " << i * 100 << "\n";
        sweep.push_back({double(i * 100) - dis + 0.5, 0, pop[i]});
        sweep.push_back({double(i * 100) + dis - 0.5, 1, pop[i]});
    }
    sort(sweep.begin(), sweep.end());
    ll cont = 0;
    for (auto it : sweep) {
        double y;
        ll z;
        tie(y, x, z) = it;
        if (x == 0) {
            cont += z;
            ans = max(ans, cont);
        } else {
            cont -= z;
        }
    }
    cout << ans << "\n";
    // for (int i = 0; i < n; i++) {
    //   cout << L[i] << " " << R[i] << "\n";
    //}
}