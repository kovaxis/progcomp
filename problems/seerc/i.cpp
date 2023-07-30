#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define repx(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define rep(i, n) repx(i, 0, n)

int main() {

    ll n;
    cin >> n;

    vector<ll> a(n);

    rep(i, n) cin >> a[i];

    vector<ll> L(n), R(n);
    rep(i, n) L[i] = i - 1;
    rep(i, n) R[i] = i + 1;
    R[n - 1] = -1;

    vector<bool> used(n, false);
    vector<ll> order(n);
    rep(i, n) order[i] = i;

    sort(order.begin(), order.end(), [&a](ll i, ll j) { return a[i] > a[j]; });
    ll ans = 0;

    for (ll i : order) {
        if (used[i]) continue;
        if (L[i] == -1 && R[i] == -1) {
            ans += a[i];
            used[i] = true;
            continue;
        }
        ll j = 0;
        if (R[i] == -1)
            j = L[i];
        else if (L[i] == -1)
            j = R[i];
        else if (a[R[i]] > a[L[i]])
            j = R[i];
        else
            j = L[i];

        ans += max(a[i], a[j]);
        if (i > j) swap(i, j);
        if (L[i] != -1)
            R[L[i]] = R[j];
        if (R[j] != -1)
            L[R[j]] = L[i];
        used[i] = true;
        used[j] = true;
    }
    cout << ans << endl;
    return 0;
}