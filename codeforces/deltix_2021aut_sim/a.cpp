#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = (int)(b); i < (int)(n); i++)
#define rep2(i, n) rep3(i, 0, (n))
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = (int)(n)-1; i >= (int)(b); i--)
#define invrep2(i, n) invrep3(i, 0, (n))
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

vector<ll> a;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        int N;
        cin >> N;
        a.resize(N);
        rep(i, N) cin >> a[i];

        ll bs = 0, mx = -1;
        rep(i, N) {
            ll b = __builtin_ctz(a[i]);
            a[i] >>= b;
            bs += b;
            if (mx == -1 || a[i] > a[mx]) mx = i;
        }
        a[mx] <<= bs;

        ll ans = 0;
        rep(i, N) ans += a[i];

        cout << ans << "\n";
    }
}
