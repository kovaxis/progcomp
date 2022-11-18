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

ll N, K;
vector<ll> a;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    rep(t, T) {
        cin >> N;
        a.resize(N);
        rep(i, N) cin >> a[i];
        cin >> K;

        ll ans = 0, d = 1e18;
        bool skip = true;
        rep(i, N) {
            if (skip) {
                ans += 1, skip = false;
                continue;
            }
            d = min(d, a[i - 1] - K);
            d += a[i] - K;
            if (d < 0) {
                d = 1e18, skip = true;
                continue;
            }
            ans += 1;
        }
        cout << ans << "\n";
    }
}
