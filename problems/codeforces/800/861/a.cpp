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
        int l, r;
        cin >> l >> r;
        int ans = l, ansmx = 0;
        repx(xx, l, min(r + 1, l + 200)) {
            int x = xx;
            int mx = 0, mn = 9;
            while (x) {
                mx = max(mx, x % 10);
                mn = min(mn, x % 10);
                x /= 10;
            }
            if (mx - mn > ansmx) {
                ans = xx;
                ansmx = mx - mn;
            }
        }
        cout << ans << "\n";
    }
}
