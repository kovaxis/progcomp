#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        int N, K;
        cin >> N >> K;
        vector<ll> a(N), b(N + 1);
        rep(i, N) cin >> a[i];

        if (K >= N) {
            ll t = K - N;
            ll ans = 0;
            rep(i, N) {
                ans += a[i] + t;
                t += 1;
            }
            cout << ans << '\n';
            continue;
        }

        b[0] = 0;
        rep(i, N) b[i + 1] = b[i] + a[i];

        ll ans = 0;
        rep(i, N) {
            if (i + K <= N) {
                ans = max(ans, b[i + K] - b[i]);
            }
        }
        rep(t, K) ans += t;
        cout << ans << "\n";
    }
}
