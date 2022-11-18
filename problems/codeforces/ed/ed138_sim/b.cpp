#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define repx(i, a, b) for (int i = a; i < b; i++)
#define rep(i, n) repx(i, 0, n)
#define invrepx(i, a, b) for (int i = b - 1; i >= a; i--)
#define invrep(i, n) invrepx(i, 0, n)

int N, s, e;
ll ans;
vector<ll> a, b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int TC;
    cin >> TC;
    while (TC--) {
        cin >> N;
        a.resize(N), b.resize(N);
        rep(i, N) cin >> a[i];
        rep(i, N) cin >> b[i];
        s = 0, e = N, ans = 0;

        rep(i, N) ans += a[i];
        while (e - s > 1) {
            if (b[s] < b[e - 1]) {
                // kill start
                ans += b[s];
                s += 1;
            } else {
                // kill end
                ans += b[e - 1];
                e -= 1;
            }
        }

        cout << ans << "\n";
    }
}
