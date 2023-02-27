#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

const ll MOD = 1e9 + 7;

int N;
vector<int> a;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    a.resize(N);
    rep(i, N) cin >> a[i];

    vector<ll> pow2(N + 1, 1);
    rep(i, N) pow2[i + 1] = pow2[i] * 2 % MOD;

    ll ans = 0;
    rep(i, N) repx(j, i + 1, N) {
        int left = lower_bound(a.begin(), a.end(), a[i] - (a[j] - a[i])) - a.begin();
        int right = a.end() - lower_bound(a.begin(), a.end(), a[j] + (a[j] - a[i]));
        ans += pow2[left + right];
        ans %= MOD;
    }

    cout << ans << endl;
}
