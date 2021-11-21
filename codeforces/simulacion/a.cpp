#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define REPGET(_1, _2, _3, NAME, ...) NAME
#define rep3(i, b, n) for (int i = b; i < n; i++)
#define rep2(i, n) rep3(i, 0, n)
#define rep(...) REPGET(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define invrep3(i, b, n) for (int i = n - 1; i >= b; i--)
#define invrep2(i, n) invrep3(i, 0, n)
#define invrep(...) REPGET(__VA_ARGS__, invrep3, invrep2)(__VA_ARGS__)

typedef long long ll;

ll a[400];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    rep(i, n) { cin >> a[i]; }
    rep(i, n, 3 * n) {
        ll minsum = a[0] + a[i - 1];
        rep(j, 1, (i + 1) / 2) {
            ll s = a[j] + a[i - j - 1];
            minsum = min(s, minsum);
        }
        a[i] = minsum;
    }
    rep(i, q) {
        int k;
        cin >> k;
        k -= 1;
        if (k < 3 * n) {
            cout << a[k] << '\n';
        } else {
            int kmod = k % n;
            ll diff = a[2 * n + kmod] - a[n + kmod];
            ll minsum = a[n + kmod] + (k - (n + kmod)) / n * diff;
            cout << minsum << '\n';
        }
    }
}
