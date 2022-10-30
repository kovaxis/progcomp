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
        int mx_x = 0, mx_y = 0;
        int mn_x = 0, mn_y = 0;
        int N;
        cin >> N;
        rep(i, N) {
            int x, y;
            cin >> x >> y;
            mn_x = min(mn_x, x);
            mn_y = min(mn_y, y);
            mx_x = max(mx_x, x);
            mx_y = max(mx_y, y);
        }
        int ans = 2 * (mx_x + mx_y - mn_x - mn_y);
        cout << ans << "\n";
    }
}
